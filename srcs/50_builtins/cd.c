/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:12 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/01 12:04:13 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd_env(t_data *data, char *var)
{
	char	cwd[BUFFER_SIZE];

	set_env_var(var, getcwd(cwd, BUFFER_SIZE), data->env, 0);
}

int	ft_cd(char **args, t_data *data)
{
	int	arg_nb;
	int	chdir_val;

	update_pwd_env(data, "OLDPWD");
	arg_nb = tab_size(args) - 1;
	if (arg_nb == 0)
	{
		chdir_val = chdir(get_var_value("HOME", data->env));
		if (chdir_val == -1)
			return (error_msg(E_STD, "cd", NULL), 0);
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
