/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:55:27 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/27 14:57:58 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_data *data)
{
	char	*cwd;

	if (args[1] && args[1][0] == '-' && args[1][1])
	{
		if (args[1][1] != '-')
			return (error_msg_cmd(E_INVALID_OPTION, "pwd: ", args[1]), 2);
		if (args[1][1] == '-' && args[1][2])
			return (error_msg_cmd(E_INVALID_OPTION, "pwd: ", args[1]), 2);
	}
	cwd = get_var_value("PWD", data->env);
	ft_putendl_fd(cwd, 1);
	return (0);
}
