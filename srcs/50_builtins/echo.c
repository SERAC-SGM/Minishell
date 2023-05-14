/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:57 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/14 19:43:15 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **attr)
{
	int	n_option;
	int	i;

	n_option = 1;
	if (!attr[1])
		return (0);
	i = 1;
	while (attr[i] && ft_strlen(attr[i]) == ft_strlen("-n")
		&& !ft_strncmp("-n", attr[i], ft_strlen("-n")))
	{
		n_option = 0;
		i++;
	}
	while (attr[i])
		ft_putstr_fd(attr[i++], 1);
	if (n_option)
		write(1, "\n", 1);
	return (0);
}
