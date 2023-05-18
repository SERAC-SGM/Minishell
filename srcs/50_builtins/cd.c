/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:12 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/18 14:09:09 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **attr, t_data *data)
{
	int	arg_nb;

	arg_nb = tab_size(attr) - 1;
	if (arg_nb == 0)
	{
		if (chdir(get_var_value("HOME", data->env)) == -1)
			return (error_msg(E_STD, "cd", NULL), 0);
	}
	if (arg_nb > 1)
		return (error_msg_cmd(E_TOO_MANY_ARG, "cd", NULL), 1);
	if (chdir(attr[1]) == -1)
		return (error_msg_cmd(E_FILE, "cd: ", attr[1]), 1);
	return (0);
}
