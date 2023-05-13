/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:57 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/14 00:12:25 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int	n_option;
	int	i;

	n_option = 1;
	if (!args[1])
		return (0);
	i = -1;
	while (args[++i]
		&& ft_strlen(args[i]) == ft_strlen("-n")
		&& !ft_strncmp("-n", args[i], ft_strlen("-n")))
		n_option = 0;
	while (args[i])
		ft_putstr(args[i++]);
	if (n_option)
		ft_putstr("\n");
	return (0);
}
