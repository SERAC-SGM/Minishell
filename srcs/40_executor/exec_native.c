/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_native.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:11 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/23 14:28:04 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if the provided path is correct.
*/
static int	is_full_path(char *cmd_path, t_data *data)
{
	DIR	*dir;

	if (!ft_strcmp(cmd_path, ".") || !ft_strcmp(cmd_path, ".."))
		exit_error(E_CMD_NOT_FOUND, cmd_path, data);
	if (!*cmd_path)
		exit_error(E_CMD_NOT_FOUND, cmd_path, data);
	dir = opendir(cmd_path);
	if (dir)
	{
		closedir(dir);
		exit_error(E_DIR, cmd_path, data);
	}
	if (*cmd_path == '/' || *cmd_path == '.')
		return (1);
	return (0);
}

static void	set_cmd_with_path(t_data *data, int proc_idx)
{
	if (is_full_path(data->cmds_tab[proc_idx].args[0], data))
	{
		if (access(data->cmds_tab[proc_idx].args[0], F_OK) == -1)
			exit_error(E_FILE, data->cmds_tab[proc_idx].name, data);
		if (access(data->cmds_tab[proc_idx].args[0], X_OK) == -1)
			exit_error(E_PERM, data->cmds_tab[proc_idx].name, data);
	}
}

static int	set_cmd(t_data *data, int proc_idx)
{
	char	*tmp;
	int		i;

	set_cmd_with_path(data, proc_idx);
	if (access(data->cmds_tab[proc_idx].args[0], F_OK | X_OK) != -1)
		return (0);
	if (!data->env_path)
		exit_error(E_CMD_NOT_FOUND, data->cmds_tab[proc_idx].name, data);
	tmp = ft_strjoin("/", data->cmds_tab[proc_idx].args[0]);
	i = 0;
	while (data->env_path[i])
	{
		free(data->cmds_tab[proc_idx].args[0]);
		data->cmds_tab[proc_idx].args[0] = ft_strjoin(data->env_path[i], tmp);
		if (access(data->cmds_tab[proc_idx].args[0], F_OK | X_OK) == 0)
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
	// int	i;

	set_cmd(data, proc_idx);
	dup_file(data, proc_idx);
	dup_pipe(data, proc_idx);
	// i = -1;
	// while (++i < data->process_nb)
		close_files(&data->cmds_tab[proc_idx]);
	close_pipe(data);
	if ((proc_idx == 0 && data->cmds_tab[proc_idx].fd_in < 0)
		|| (proc_idx == data->process_nb - 1 && data->cmds_tab[proc_idx].fd_out
			< 0))
		exit_error(E_NOMSG, 0, data);
	execve(data->cmds_tab[proc_idx].args[0],
		data->cmds_tab[proc_idx].args, env);
}
