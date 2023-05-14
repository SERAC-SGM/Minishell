/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:49:12 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/14 19:40:44 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **attr)
{
	int	arg_nb;
	
	arg_nb = tab_size(attr) - 1;
	if (arg_nb < 1)
		return (error_msg(E_TOO_FEW_ARG, "cd", NULL), 0);
	if (arg_nb > 1)
		return (error_msg(E_TOO_MANY_ARG, "cd", NULL), 0);
	if (chdir(attr[1]) == -1)
		return (error_msg(E_STD, "cd", NULL), 0);
	return (0);
}
