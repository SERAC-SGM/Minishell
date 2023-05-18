/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_native.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:11 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/18 13:55:48 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_cmd(t_data *data, int proc_idx)
{
	char	*tmp;
	int		i;

	if (access(data->cmds_tab[proc_idx].attr[0], F_OK) != -1)
		return (0);
	tmp = ft_strjoin("/", data->cmds_tab[proc_idx].attr[0]);
	i = 0;
	while (data->env_path[i])
	{
		data->cmds_tab[proc_idx].attr[0] = ft_strjoin(data->env_path[i], tmp);
		if (access(data->cmds_tab[proc_idx].attr[0], F_OK) != -1)
		{
			data->cmds_tab[proc_idx].attr[0] = data->env_path[i];
			break ;
		}
		if (data->env_path[i + 1])
			free(data->cmds_tab[proc_idx].attr[0]);
		i++;
	}
	free(tmp);
	if (!data->env_path[i])
		exit_error(E_CMD_NOT_FOUND, data->cmds_tab[proc_idx].attr[0], data);
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
	execve(data->cmds_tab[proc_idx].attr[0], data->cmds_tab[proc_idx].attr,	env);
}
