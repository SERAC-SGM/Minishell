/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:57 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/25 11:26:43 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char **args)
{
	int	end_newline;
	int	i;

	end_newline = 1;
	if (!args[1])
		return (write(1, "\n", 1), 0);
	i = 0;
	while (args[++i] && args[i][0] == '-')
	{
		if (args[i][1] == 'n')
			end_newline = 0;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], 1);
		if (args[i])
			write(1, " ", 1);
	}
	if (end_newline)
		write(1, "\n", 1);
	return (0);
}
