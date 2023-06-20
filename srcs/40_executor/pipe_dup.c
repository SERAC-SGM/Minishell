/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:24:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/20 16:15:05 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->process_nb - 1)
	{
		if (pipe(data->fd[i]) == -1)
			exit_error(E_PIPE, 0, data);
	}
}

void	close_pipe(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->process_nb - 1)
	{
		close(data->fd[i][0]);
		close(data->fd[i][1]);
	}
}

void	dup_in_out(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
}

void	dup_pipe(t_data *data, int proc_idx)
{
	if (!data->cmds_tab[proc_idx].infile && proc_idx > 0)
		dup2(data->fd[proc_idx - 1][0], STDIN_FILENO);
	if (!data->cmds_tab[proc_idx].outfile && proc_idx < data->process_nb - 1)
		dup2(data->fd[proc_idx][1], STDOUT_FILENO);
}

void	dup_file(t_data *data, int proc_idx)
{
	if (data->cmds_tab[proc_idx].infile)
		dup2(data->cmds_tab[proc_idx].fd_in, STDIN_FILENO);
	if (data->cmds_tab[proc_idx].outfile)
		dup2(data->cmds_tab[proc_idx].fd_out, STDOUT_FILENO);
}
