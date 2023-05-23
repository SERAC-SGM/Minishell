/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:24:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/23 15:27:17 by lletourn         ###   ########.fr       */
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

void	dup_first_cmd(t_data *data)
{
	if (data->cmds_tab[0].infile)
		dup2(data->cmds_tab[0].fd_in, STDIN_FILENO);
	if (data->cmds_tab[0].outfile)
		dup2(data->cmds_tab[0].fd_out, STDOUT_FILENO);
	else
		dup2(data->fd[0][1], STDOUT_FILENO);
}

void	dup_last_cmd(t_data *data)
{
	if (data->cmds_tab[data->process_nb - 1].infile)
		dup2(data->cmds_tab[data->process_nb - 1].fd_in, STDIN_FILENO);
	else
		dup2(data->fd[data->process_nb - 2][0], STDIN_FILENO);
	if (data->cmds_tab[0].outfile)
		dup2(data->cmds_tab[0].fd_out, STDOUT_FILENO);
}

void	dup_fds(t_data *data, int proc_idx)
{
	int	fd_in;
	int	fd_out;

	if (proc_idx == 0)
		dup_first_cmd(data);
	else if (proc_idx == data->process_nb - 1)
		dup_last_cmd(data);
	else
	{
		if (data->cmds_tab[proc_idx].infile)
			fd_in = data->cmds_tab[proc_idx].fd_in;
		else
			fd_in = data->fd[proc_idx][0];
		if (data->cmds_tab[proc_idx].outfile)
			fd_out = data->cmds_tab[proc_idx].fd_out;
		else
			fd_out = data->fd[proc_idx - 1][1];
		dup_in_out(fd_in, fd_out);
	}
}
