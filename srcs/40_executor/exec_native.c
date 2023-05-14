/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_native.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:09:28 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/13 17:39:13 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_cmd(t_data *data, int proc_idx)
{
	char	*tmp;
	int		i;

	if (access(data->cmds[proc_idx]->attr[0], F_OK) != -1)
		return (0);
	tmp = ft_strjoin("/", data->cmds[proc_idx]->attr[0]);
	i = 0;
	while (data->env_path[i])
	{
		data->cmds[proc_idx]->attr[0] = ft_strjoin(data->env_path[i], tmp);
		if (access(data->cmds[proc_idx]->attr[0], F_OK) != -1)
		{
			data->cmds[proc_idx]->path = data->env_path[i];
			break ;
		}
		if (data->env_path[i + 1])
			free(data->cmds[proc_idx]->attr[0]);
		i++;
	}
	free(tmp);
	if (!data->env_path[i])
		exit_error(E_CMD, data->cmds[proc_idx]->name, data);
	return (0);
}

void	exec_native(t_data *data, int proc_idx, char **env)
{	
	set_cmd(proc_idx, data);
	if (data->nb_process != 1)
		close_pipe(data);
	if ((proc_idx == 0 && data->fd_in < 0)
		|| (proc_idx == data->nb_process - 1 && data->fd_out < 0))
		exit_error(E_NOMSG, 0, data);
	execve(data->cmds[proc_idx]->data[0], data->cmds[proc_idx]->data, env);
}
