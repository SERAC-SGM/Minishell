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

void	process(t_data *data, int proc_idx)
{	
	char	**env;

	set_cmd(proc_idx, info);
	if (proc_idx == 0)
		dup_in_out(info->fd_in, info->fd[1]);
	else if (proc_idx == info->nb_process - 1)
		dup_in_out(info->fd[2 * (proc_idx - 1)], info->fd_out);
	else
		dup_in_out(info->fd[2 * (proc_idx - 1)], info->fd[2 * proc_idx + 1]);
	close_pipe(info);
	if ((proc_idx == 0 && info->fd_in < 0)
		|| (proc_idx == info->nb_process - 1 && info->fd_out < 0))
		exit_error(E_NOMSG, 0, info);
	env = env_to_tab(data->env);
	execve(info->cmds[proc_idx]->data[0], info->cmds[proc_idx]->data, env);
}
