/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/28 13:08:20 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	open_files(t_cmd *cmd)
{
	if (cmd->fd_in < 0 || cmd->fd_out < 0)
		return ;
	if (cmd->infile)
		cmd->fd_in = open(cmd->infile, O_RDONLY, 0644);
	if (cmd->outfile)
	{
		if (!cmd->append)
		cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
}

