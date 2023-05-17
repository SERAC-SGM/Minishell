/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:03:56 by matnam            #+#    #+#             */
/*   Updated: 2023/05/17 12:59:08 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char	**args, t_list *env, t_list *set)
{
	(void)args;
	(void)set;
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}
