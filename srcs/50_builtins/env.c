/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:30:05 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/16 17:29:01 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_list *env, char **attr)
{
	int	arg_nb;

	arg_nb = tab_size(attr) - 1;
	if (arg_nb > 1)
		return (error_msg(E_TOO_MANY_ARG, "env", NULL), (void)0);
	while (env)
	{
		ft_putendl_fd(env->line, 1);
		env = env->next;
	}
}
