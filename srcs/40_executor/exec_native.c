/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_native.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:11 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/22 16:11:03 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_cmd_with_path(t_data *data, int proc_idx)
{
	if (!ft_strncmp(data->cmds_tab[proc_idx].attr[0], "./", 2)
		|| !ft_strncmp(data->cmds_tab[proc_idx].attr[0], "/", 1))
	{
		if (access(data->cmds_tab[proc_idx].attr[0], F_OK) == -1)
			exit_error(E_CMD_NOT_FOUND, data->cmds_tab[proc_idx].name, data);
		if (access(data->cmds_tab[proc_idx].attr[0], X_OK) == -1)
			exit_error(E_PERM, data->cmds_tab[proc_idx].name, data);
	}
}

static int	set_cmd(t_data *data, int proc_idx)
{
	char	*tmp;
	int		i;

	set_cmd_with_path(data, proc_idx);
	if (access(data->cmds_tab[proc_idx].attr[0], F_OK) != -1)
		return (0);
	tmp = ft_strjoin("/", data->cmds_tab[proc_idx].attr[0]);
	i = 0;
	while (data->env_path[i])
	{
		free(data->cmds_tab[proc_idx].attr[0]);
			data->cmds_tab[proc_idx].attr[0]
			= ft_strjoin(data->env_path[i], tmp);
		if (access(data->cmds_tab[proc_idx].attr[0], F_OK | X_OK) == 0)
			break ;
		i++;
	}
	free(tmp);
	if (!data->env_path[i])
		exit_error(E_CMD_NOT_FOUND, data->cmds_tab[proc_idx].name, data);
	return (0);
}

void	exec_native(t_data *data, int proc_idx, char **env)
{	
	set_cmd(data, proc_idx);
	if (data->process_nb != 1)
		close_pipe(data);
	if ((proc_idx == 0 && data->cmds_tab[proc_idx].fd_in < 0)
		|| (proc_idx == data->process_nb - 1 && data->cmds_tab[proc_idx].fd_out
			< 0))
		exit_error(E_NOMSG, 0, data);
	execve(data->cmds_tab[proc_idx].attr[0],
		data->cmds_tab[proc_idx].attr, env);
}
