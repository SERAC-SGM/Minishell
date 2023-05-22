/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:49 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/22 15:37:16 by maaliber         ###   ########.fr       */
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

static int	is_builtin(char *name)
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
	if (ft_strcmp(name, "unset") == 0)
		return (1);
	if (ft_strcmp(name, "exit") == 0)
		return (1);
	return (0);
}

static void	exec_single_cmd(t_data *data, int proc_idx, char **env)
{
	if (!data->cmds_tab[proc_idx].attr)
		return ;
	if (is_builtin(data->cmds_tab[proc_idx].attr[0]))
		g_sig.error_status = exec_builtin(data, proc_idx);
	else
	{
		g_sig.pid = fork();
		if (g_sig.pid == -1)
			exit_error(E_FORK, 0, data);
		if (g_sig.pid == 0)
		{
			update_signal();
			exec_native(data, proc_idx, env);
		}
	}
	if (g_sig.pid == 0)
		clear_exit(data);
	close_pipe(data);
}

static void	exec_multiple_cmd(t_data *data, int proc_idx, char **env)
{
	open_pipe(data);
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		exit_error(E_FORK, 0, data);
	if (g_sig.pid == 0)
	{
		update_signal();
		dup_fds(data, proc_idx);
		exec_single_cmd(data, proc_idx, env);
	}
}

int	exec_cmd_line(t_data *data)
{
	char	**env;
	int		proc_idx;

	env = env_to_tab(data->env);
	proc_idx = 0;	
	while (proc_idx < data->process_nb)
	{
		if (data->process_nb == 1)
			exec_single_cmd(data, proc_idx, env);
		else
			exec_multiple_cmd(data, proc_idx, env);
		proc_idx++;
	}
	free(env);
	return (0);
}
