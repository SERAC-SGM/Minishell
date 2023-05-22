/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:24:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/22 16:03:45 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->process_nb - 1)
	{
		if (pipe(&data->fd[2 * i]) == -1)
			exit_error(E_PIPE, 0, data);
		i++;
	}
}

void	close_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->process_nb - 1)
	{
		close(data->fd[2 * i]);
		close(data->fd[2 * i + 1]);
		i++;
	}
}

void	dup_in_out(int fd_in, int fd_out)
{
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
}

void	dup_fds(t_data *data, int proc_idx)
{
	int	fd_in;
	int	fd_out;

	if (data->cmds_tab[proc_idx].fd_in != 0
		|| data->process_nb == 1 || proc_idx == 0)
		fd_in = data->cmds_tab[proc_idx].fd_in;
	else
		fd_in = data->fd[2 * (proc_idx - 1)];
	if (data->cmds_tab[proc_idx].fd_out != 1
		|| data->process_nb == 1 || proc_idx == data->process_nb - 1)
		fd_out = data->cmds_tab[proc_idx].fd_out;
	else
		fd_out = data->fd[2 * proc_idx + 1];
	dup_in_out(fd_in, fd_out);
}
