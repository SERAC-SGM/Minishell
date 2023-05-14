/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 12:55:27 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/14 19:45:01 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		pwd(void)
{
	char	cwd[BUFFER_SIZE];

	if (getcwd(cwd, BUFFER_SIZE))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	else
		return (1);
}