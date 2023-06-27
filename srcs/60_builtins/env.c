/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:30:05 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/04 18:13:23 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_list *env, char **args)
{
	int	arg_nb;

	arg_nb = tab_size(args) - 1;
	if (arg_nb > 1)
		return (error_msg(E_TOO_MANY_ARG, "env"), (void)0);
	while (env)
	{
		ft_putendl_fd(env->line, 1);
		env = env->next;
	}
}
