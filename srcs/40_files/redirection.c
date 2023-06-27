/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:14:45 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/27 18:16:58 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Redirect infile
*/
static void	in_redir(t_tkn_lst *token, t_cmd *cmd)
{
	int	fd;

	if (!token->next->content || cmd->fd_in == -1 || cmd->fd_out == -1)
		return ;
	if (access(token->next->content, F_OK) != 0)
	{
		cmd->fd_in = -1;
		error_msg(E_FILE, token->next->content);
		return ;
	}
	fd = open(token->next->content, O_RDONLY);
	if (fd < 0)
	{
		cmd->fd_in = -1;
		error_msg(E_PERM, token->next->content);
		return ;
	}
	if (!isatty(fd))
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = ft_strdup(token->next->content);
	}
	close(fd);
}

/*
Redirect infile if heredoc is declared
*/
static void	hdoc_redir(t_tkn_lst *token, t_cmd *cmd, t_data *data)
{
	if (!token->next->content || cmd->fd_in == -1 || cmd->fd_out == -1)
		return ;
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	cmd->delimiter = token->next->content;
	cmd->here_doc = 1;
	(void)data;
	// input_heredoc(cmd, data)
}

/*
Redirect outfile
*/
static void	out_redir(t_tkn_lst *token, t_cmd *cmd)
{
	int	fd;

	if (!token->next->content || cmd->fd_in == -1 || cmd->fd_out == -1)
		return ;
	fd = open(token->next->content, O_WRONLY, O_CREAT, 0655);
	if (fd < 0)
	{
		cmd->fd_in = -1;
		error_msg(E_PERM, token->next->content);
		return ;
	}
	if (!isatty(fd))
	{
		cmd->outfile = token->next->content;
		if (token->type == APPEND)
			cmd->append = 1;
	}
	close(fd);
}

void	redirection(t_tkn_lst *token, t_cmd *cmd, t_data *data)
{
	if (token->type == RD_IN)
		in_redir(token, cmd);
	else if (token->type == HERE)
		hdoc_redir(token, cmd, data);
	else if (token->type == RD_OUT || token->type == APPEND)
		out_redir(token, cmd);
	// if (!input_files(cmd))
	// 	return (free(env), g_sig.error_status = 130, 0);
}
