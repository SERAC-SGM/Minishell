/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:57 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/24 12:25:44 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	n_option;
	int	i;

	n_option = 1;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i] && ft_strlen(args[i]) == ft_strlen("-n")
		&& !ft_strncmp("-n", args[i], ft_strlen("-n")))
	{
		n_option = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i + 1])
			write(1, " ", 1);
	}
	if (n_option)
		write(1, "\n", 1);
	return (0);
}
