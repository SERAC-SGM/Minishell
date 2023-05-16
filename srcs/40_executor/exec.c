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

static char	**env_to_tab(t_list	*env)
{
	char	**env_tab;
	int		i;

	env_tab = malloc((ft_lstsize(env) + 1) * sizeof(char *));
	if (!env_tab)
		return (error_msg(E_MEM, NULL, NULL), NULL);
	i = 0;
	while (env)
	{
		env_tab[i++] = env->line;
		env = env->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

static int		is_builtin(char *name)
{
	if (ft_strcmp(name, "echo") == 0)
		return (1);
	if (ft_strcmp(name, "cd") == 0)
		return (1);
	if (ft_strcmp(name, "pwd") == 0)
		return (1);
	if (ft_strcmp(name, "env") == 0)
		return (1);
	if (ft_strcmp(name, "export") == 0)
		return (1);
	return (0);
}

static void	exec_cmd(t_data *data, int proc_idx, char **env)
{
	if (is_builtin(data->cmds_tab[proc_idx].attr[0]))
		exec_builtin(data, proc_idx);
	else
	{
		if (data->process_nb  == 1)
		{	
			g_sig.pid = fork();
			if (g_sig.pid == -1)
				exit_error(E_FORK, 0, data);
		}
		if (g_sig.pid == 0)
			exec_native(data, proc_idx, env);
	}
	close_pipe(data);
}

int	exec_cmd_line(t_data *data)
{
	char	**env;
	int		proc_idx;
	int		status;
	
	env = env_to_tab(data->env);
	proc_idx = 0;
	while (proc_idx < data->process_nb)
	{
		if (data->process_nb  == 1)
			exec_cmd(data, proc_idx, env);
		else
		{
			open_pipe(data);
			g_sig.pid = fork();
			if (g_sig.pid == -1)
				exit_error(E_FORK, 0, data);
			if (g_sig.pid == 0)
			{
				dup_fds(data, proc_idx);
				exec_cmd(data, proc_idx, env);
			}
		}
		proc_idx++;
	}
	while (waitpid(-1, &status, 0) != -1)
		;
	return (0);
}
