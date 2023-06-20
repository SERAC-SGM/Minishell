/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/20 16:15:40 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_open_error(int fd, t_cmd *cmd)
{
	if (fd == -1)
		error_msg(E_PERM, cmd->infile);
}

void	open_files(t_cmd *cmd)
{
	if (cmd->infile)
	{
		cmd->fd_in = open(cmd->infile, O_RDONLY, 0644);
		check_open_error(cmd->fd_in, cmd);
	}
	if (cmd->outfile)
	{
		if (!cmd->append)
		cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
		check_open_error(cmd->fd_out, cmd);
	}
}

void	unlink_heredoc(t_cmd *cmd)
{
	if (cmd->here_doc)
		unlink(cmd->infile);
}

void	close_files(t_cmd *cmd)
{
	// ft_printf("INDEX:%d->%s:%d\n", cmd->process_index, cmd->infile, cmd->fd_in);
	if (cmd->infile)
	{
		free(cmd->infile);
		if (isatty(cmd->fd_in) == 1)
			close(cmd->fd_in);
		cmd->infile = NULL;
	}
	// ft_printf("INDEX:%d->%s:%d\n", cmd->process_index, cmd->outfile, cmd->fd_out);
	if (cmd->outfile)
	{
		if (isatty(cmd->fd_out) == 1)
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
