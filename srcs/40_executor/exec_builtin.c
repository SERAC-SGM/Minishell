/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:36 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/26 12:01:47 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Duplicates the stdin and stdout.
*/
static void	save_reset_stdin_out(int i)
{
	static int	saved_stdin;
	static int	saved_stdout;

	if (i == 0)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
	}
}

int	exec_builtin(t_data *data, int proc_idx)
{
	int	ret;

	save_reset_stdin_out(0);
	dup_file(data, proc_idx);
	dup_pipe(data, proc_idx);
	close_all_files(data);
	close_pipe(data);
	ret = 0;
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "echo") == 0)
		ret = ft_echo(data->cmds_tab[proc_idx].args);
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "cd") == 0)
		ret = ft_cd(data->cmds_tab[proc_idx].args, data);
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "pwd") == 0)
		ret = ft_pwd();
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "env") == 0)
		ft_env(data->env, data->cmds_tab[proc_idx].args);
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "export") == 0)
		ret = ft_export(data->cmds_tab[proc_idx].args, data);
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "unset") == 0)
		ft_unset(data->cmds_tab[proc_idx].args, data);
	if (ft_strcmp(data->cmds_tab[proc_idx].args[0], "exit") == 0)
		ft_exit();
	save_reset_stdin_out(1);
	return (ret);
}
