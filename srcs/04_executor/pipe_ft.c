/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:24:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/13 17:42:41 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_process - 1)
	{
		if (pipe(&data->fd[2 * i]) == -1)
			exit_error(E_PIPE, 0, data);
		i++;
	}
}

void	dup_in_out(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

void	close_pipe(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_process - 1)
	{
		close(data->fd[2 * i]);
		close(data->fd[2 * i + 1]);
		i++;
	}
}
