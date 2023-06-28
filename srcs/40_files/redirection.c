/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:14:45 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/28 13:51:01 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Redirect infile
*/
static int	in_redir(t_tkn_lst *token, t_cmd *cmd, int err_msg)
{
	int	fd;

	if (!token->next->content || cmd->fd_in == -1 || cmd->fd_out == -1)
		return (0);
	if (access(token->next->content, F_OK) != 0)
	{
		if (!err_msg)
			error_msg(E_FILE, token->next->content);
		return (cmd->fd_in = -1, 1);
	}
	fd = open(token->next->content, O_RDONLY);
	if (fd < 0)
	{
		if (!err_msg)
			error_msg(E_PERM, token->next->content);
		return (cmd->fd_in = -1, 1);
	}
	if (!isatty(fd))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(token->next->content);
	}
	return (close(fd), 0);
}

/*
Redirect outfile
*/
static int	out_redir(t_tkn_lst *token, t_cmd *cmd, int err_msg)
{
	int	fd;

	if (!token->next->content || cmd->fd_in == -1 || cmd->fd_out == -1)
		return (0);
	fd = open(token->next->content, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
	{
		if (!err_msg)
			error_msg(E_PERM, token->next->content);
		return (cmd->fd_out = -1, 1);
	}
	if (!isatty(fd))
	{
		cmd->outfile = token->next->content;
		if (token->type == APPEND)
			cmd->append = 1;
	}
	close(fd);
	return (0);
}

static char	*heredoc_name(int proc_nb)
{
	char	*name;
	char	*nb;

	nb = ft_itoa(proc_nb);
	name = ft_strjoin(".here_doc", nb);
	free(nb);
	return (name);
}

/*
Redirect infile if heredoc is declared
*/
static void	hdoc_redir(t_tkn_lst *token, t_cmd *cmd, t_data *data)
{
	int		proc_idx;

	if (!token->next->content)
		return ;
	if (!cmd->infile_hdoc)
		cmd->infile_hdoc = heredoc_name(cmd->process_index);
	if (ft_strcmp(cmd->infile, cmd->infile_hdoc))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(cmd->infile_hdoc);
	}
	cmd->delimiter = token->next->content;
	cmd->here_doc = 1;
	if (!input_heredoc(cmd, data))
	{
		g_sig.error_status = 130;
		proc_idx = cmd->process_index;
		while (proc_idx >= 0)
			close_files(&data->cmds_tab[proc_idx--]);
	}
}

void	redirection(t_tkn_lst *token, t_cmd *cmd, t_data *data, int reset)
{
	static int	err_msg;
	static int	proc_idx;

	if (reset)
		return (err_msg = 0, (void)0);
	if (!token)
		return ;
	if (proc_idx != cmd->process_index)
	{
		err_msg = 0;
		proc_idx = cmd->process_index;
	}
	if (token->type == RD_IN)
		err_msg += in_redir(token, cmd, err_msg);
	if (token->type == RD_OUT || token->type == APPEND)
		err_msg += out_redir(token, cmd, err_msg);
	if (token->type == HERE)
		hdoc_redir(token, cmd, data);
}
