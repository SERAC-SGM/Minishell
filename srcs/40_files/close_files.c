/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:25:40 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/28 11:45:12 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_infile(t_data *data, int proc_idx)
{
	int	i;

	i = -1;
	while (++i <= proc_idx)
	{
		if (data->cmds_tab[i].infile)
		{
			if (data->cmds_tab[i].fd_in > 2)
				close(data->cmds_tab[i].fd_in);
			free(data->cmds_tab[i].infile);
		}
		if (data->cmds_tab[i].infile_hdoc)
			free(data->cmds_tab[i].infile_hdoc);
	}
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

void	close_all_files(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->process_nb)
		close_files(&data->cmds_tab[i]);
}
