/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/22 17:20:53 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_files(t_cmd *cmd)
{
	char	*infile;

	if (cmd->infile)
		infile = cmd->infile;
	else
		infile = cmd->infile_hdoc;
	if (infile)
		cmd->fd_in = open(infile, O_RDONLY, 0644);
	if (cmd->fd_in == -1)
		error_msg(E_PERM, infile);
	if (cmd->outfile)
	{
		if (!cmd->append)
		cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	if (cmd->fd_out == -1)
		error_msg(E_PERM, cmd->outfile);
}

void	unlink_heredoc(t_cmd *cmd)
{
	if (cmd->here_doc)
		unlink(cmd->infile_hdoc);
}

void	close_files(t_cmd *cmd)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		if (!isatty(cmd->fd_in) && cmd->fd_in >= 0)
			close(cmd->fd_in);
		cmd->infile = NULL;
	}
	if (cmd->infile_hdoc)
	{
		free(cmd->infile_hdoc);
		if (!isatty(cmd->fd_in) && cmd->fd_in >= 0)
			close(cmd->fd_in);
		cmd->infile_hdoc = NULL;
	}
	if (cmd->outfile)
	{
		if (!isatty(cmd->fd_out) && cmd->fd_out >= 0)
			close(cmd->fd_out);
		cmd->outfile = NULL;
	}
}

int	input_files(t_data *data)
{
	int		proc_idx;

	proc_idx = -1;
	while (++proc_idx < data->process_nb)
	{
		if (data->cmds_tab[proc_idx].here_doc)
		{
			if (!input_heredoc(&data->cmds_tab[proc_idx], data))
			{
				while (proc_idx >= 0)
					close_files(&data->cmds_tab[proc_idx--]);
				return (0);
			}
		}
		open_files(&data->cmds_tab[proc_idx]);
	}
	return (1);
}
