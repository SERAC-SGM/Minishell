/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:49 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/27 16:40:09 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Waits for each process to finish.
*/
static void	wait_process(void)
{
	int	status;

	disable_signal();
	status = 0;
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
	{
		if (g_sig.error_status == 0)
			g_sig.error_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		g_sig.error_status = WTERMSIG(status) + 128;
		if (g_sig.error_status == 131)
			ft_putstr_fd("Quit: (core dumped)\n", STDERR_FILENO);
		if (g_sig.error_status == 130)
			ft_putstr_fd("\n", STDERR_FILENO);
	}
	enable_signal();
}

/*
Checks if the name correstponds to a builtin.
*/
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
	if (data->cmds_tab[proc_idx].fd_in == -1
		|| data->cmds_tab[proc_idx].fd_out == -1)
		return (g_sig.error_status = 1, (void)0);
	if (!data->cmds_tab[proc_idx].args)
		return ;
	if (is_builtin(data->cmds_tab[proc_idx].args[0]))
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
}

static void	exec_multiple_cmd(t_data *data, int proc_idx, char **env)
{
	if (data->cmds_tab[proc_idx].fd_in == -1
		|| data->cmds_tab[proc_idx].fd_out == -1)
		return (g_sig.error_status = 1, (void)0);
	if (!data->cmds_tab[proc_idx].args)
		return ;
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		exit_error(E_FORK, 0, data);
	if (g_sig.pid == 0)
	{
		update_signal();
		if (is_builtin(data->cmds_tab[proc_idx].args[0]))
			g_sig.error_status = exec_builtin(data, proc_idx);
		else
			exec_native(data, proc_idx, env);
		clear_exit(data);
	}
}

int	exec_cmd_line(t_data *data)
{
	char	**env;
	int		proc_idx;

	env = env_to_tab(data->env);
	g_sig.error_status = 0;
	if (!input_files(data))
		return (free(env), g_sig.error_status = 130, 0);
	proc_idx = -1;
	open_pipe(data);
	while (++proc_idx < data->process_nb)
	{
		if (data->process_nb == 1)
			exec_single_cmd(data, proc_idx, env);
		else
			exec_multiple_cmd(data, proc_idx, env);
		unlink_heredoc(&data->cmds_tab[proc_idx]);
		close_files(&data->cmds_tab[proc_idx]);
	}
	close_pipe(data);
	free(env);
	wait_process();
	return (0);
}
