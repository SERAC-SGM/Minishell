/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:12 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/16 11:46:37 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **attr, t_data *data)
{
	int	arg_nb;
	
	arg_nb = tab_size(attr) - 1;
	if (chdir(get_var_value("HOME", data->env)) == -1)
		return (error_msg(E_STD, "cd", NULL), 0);
	if (arg_nb > 1)
		return (error_msg(E_TOO_MANY_ARG, "cd", NULL), 0);
	if (chdir(attr[1]) == -1)
		return (error_msg(E_STD, "cd", NULL), 0);
	return (0);
}
