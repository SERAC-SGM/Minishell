/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:38:47 by maaliber            #+#    #+#             */
/*   Updated: 2023/05/13 17:39:01 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**get_envpath(char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp("PATH", env[i], 4))
			break ;
		i++;
	}
	path = ft_split(env[i] + 5, ':');
	return (path);
}

int	set_cmd(int p_no, t_data *data)
{
	char	*tmp;
	int		i;

	if (access(info->cmds[p_no]->data[0], F_OK) != -1)
		return (0);
	tmp = ft_strjoin("/", info->cmds[p_no]->name);
	i = 0;
	while (info->env_path[i])
	{
		info->cmds[p_no]->data[0] = ft_strjoin(info->env_path[i], tmp);
		if (access(info->cmds[p_no]->data[0], F_OK) != -1)
		{
			info->cmds[p_no]->path = info->env_path[i];
			break ;
		}
		if (info->env_path[i + 1])
			free(info->cmds[p_no]->data[0]);
		i++;
	}
	free(tmp);
	if (!info->env_path[i])
		exit_error(E_CMD, info->cmds[p_no]->name, info);
	return (0);
}

void	process(int p_no, t_data *data, char **env)
{	
	set_cmd(p_no, info);
	if (p_no == 0)
		dup_in_out(info->fd_in, info->fd[1]);
	else if (p_no == info->nb_process - 1)
		dup_in_out(info->fd[2 * (p_no - 1)], info->fd_out);
	else
		dup_in_out(info->fd[2 * (p_no - 1)], info->fd[2 * p_no + 1]);
	close_pipe(info);
	if ((p_no == 0 && info->fd_in < 0)
		|| (p_no == info->nb_process - 1 && info->fd_out < 0))
		exit_error(E_NOMSG, 0, info);
	execve(info->cmds[p_no]->data[0], info->cmds[p_no]->data, env);
}

int	exec(t_data *data)
{
	int		p_no;

	open_pipe(data);
	while (p_no < data->nb_process)
	{
		p_id = fork();
		if (p_id == -1)
			exit_error(E_FORK, 0, info);
		if (p_id == 0)
			process(p_no, info, env);
		p_no++;
	}
	close_pipe(info);
	free_ppx(info);
	while (waitpid(-1, &status, 0) != -1)
		;
	return (0);
}
