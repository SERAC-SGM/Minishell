/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:49 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/13 14:08:56 by lletourn         ###   ########.fr       */
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
		g_sig.error_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig.error_status = WTERMSIG(status) + 128;
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
	if (!data->cmds_tab[proc_idx].args)
		return ;
	if (data->cmds_tab[proc_idx].here_doc == -1)
	{
		close_files(&data->cmds_tab[proc_idx]);
		close_pipe(data);
		error_msg(E_HEREDOC, data->cmds_tab[proc_idx].delimiter);
		return ;
	}
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
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		exit_error(E_FORK, 0, data);
	if (g_sig.pid == 0)
	{
		if (data->cmds_tab[proc_idx].here_doc == -1)
		{
			close_files(&data->cmds_tab[proc_idx]);
			close_pipe(data);
			exit_error(E_HEREDOC, data->cmds_tab[proc_idx].delimiter, data);
		}
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
	proc_idx = -1;
	while (++proc_idx < data->process_nb)
		exec_open_files(data, proc_idx);
	proc_idx = -1;
	open_pipe(data);
	while (++proc_idx < data->process_nb)
	{
		if (data->process_nb == 1)
			exec_single_cmd(data, proc_idx, env);
		else
			exec_multiple_cmd(data, proc_idx, env);
		close_files(&data->cmds_tab[proc_idx]);
	}
	close_pipe(data);
	free(env);
	wait_process();
	return (0);
}
