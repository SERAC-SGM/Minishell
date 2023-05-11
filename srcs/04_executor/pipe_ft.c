/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:24:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 14:59:27 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe(t_ppx *info)
{
	int	i;

	i = 0;
	while (i < info->nb_process - 1)
	{
		if (pipe(&info->fd[2 * i]) == -1)
			exit_error(E_PIPE, 0, info);
		i++;
	}
}

void	dup_in_out(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	close_pipe(t_ppx *info)
{
	int	i;

	i = 0;
	while (i < info->nb_process - 1)
	{
		close(info->fd[2 * i]);
		close(info->fd[2 * i + 1]);
		i++;
	}
}
