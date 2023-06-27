/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:12 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/27 16:36:35 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Updates environment variable PWD and OLD_PWD
when using cd builtin.
*/
static void	update_pwd_env(t_data *data, char *var)
{
	char	cwd[BUFFER_SIZE];

	if (!ft_strcmp(var, "OLDPWD"))
	{
		if (!get_var_value("PWD", data->env))
			return ;
		set_env_var(var, getcwd(cwd, BUFFER_SIZE), data, 0);
	}
	else
		set_env_var(var, getcwd(cwd, BUFFER_SIZE), data, 0);
}

/*
Checks if the provided path is correct.
*/
static int	is_full_path(char *cmd_path, t_data *data)
{
	DIR	*dir;

	(void) data;
	if (!cmd_path)
		return (1);
	if (ft_strncmp(cmd_path, "/", 1))
		return (0);
	dir = opendir(cmd_path);
	if (!dir)
		return (error_msg_cmd(E_FILE, "cd: ", cmd_path), 0);
	else
		closedir(dir);
	return (1);
}

int	ft_cd(char **args, t_data *data)
{
	int		arg_nb;
	int		chdir_val;
	char	cwd[BUFFER_SIZE];

	if (!getcwd(cwd, BUFFER_SIZE) && !is_full_path(args[1], data))
		return (error_msg_cmd(E_HOME_NOT_SET, "cd", NULL), 1);
	update_pwd_env(data, "OLDPWD");
	arg_nb = tab_size(args) - 1;
	if (arg_nb == 0)
	{
		if (get_var_value("HOME", data->env))
			chdir_val = chdir(get_var_value("HOME", data->env));
		else
			return (error_msg_cmd(E_HOME_NOT_SET, "cd", NULL), 1);
		update_pwd_env(data, "PWD");
		return (0);
	}
	if (arg_nb > 1)
		return (error_msg_cmd(E_TOO_MANY_ARG, "cd", NULL), 1);
	chdir_val = chdir(args[1]);
	if (chdir_val == -1)
		return (error_msg_cmd(E_FILE, "cd: ", args[1]), 1);
	update_pwd_env(data, "PWD");
	return (0);
}
