/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/04 18:12:22 by matnam           ###   ########.fr       */
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

void	close_files(t_cmd *cmd)
{
	if (cmd->infile || cmd->here_doc)
	{
		close(cmd->fd_in);
		if (cmd->here_doc)
		{
			unlink(cmd->infile);
			free(cmd->infile);
			cmd->infile = NULL;
		}
	}
	if (cmd->outfile)
	{
		close(cmd->fd_out);
		cmd->outfile = NULL;
	}
}
