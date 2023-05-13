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

int		is_builtin(char **cmd_attr, int proc_idx)
{
	if (ft_strcmp(cmd_attr[proc_idx], "echo") == 0)
		return (1);
	if (ft_strcmp(cmd_attr[proc_idx], "cd") == 0)
		return (1);
	if (ft_strcmp(cmd_attr[proc_idx], "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd_attr[proc_idx], "env") == 0)
		return (1);
	if (ft_strcmp(cmd_attr[proc_idx], "export") == 0)
		return (1);
	return (0);
}

int	exec_cmd(t_data *data)
{
	int	i;
	
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
