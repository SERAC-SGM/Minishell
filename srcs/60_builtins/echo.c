/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 11:10:57 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/01 12:05:30 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	end_newline_param(char **args, int *i)
{
	int	newline;
	int	j;

	newline = 1;
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		while (args[*i][j] && args[*i][j] == 'n')
			j++;
		if (!args[*i][j])
			newline = 0;
		else
			break ;
		(*i)++;
	}
	return (newline);
}

int	ft_echo(char **args)
{
	int	end_newline;
	int	i;

	if (!args[1])
		return (write(1, "\n", 1), 0);
	i = 1;
	end_newline = end_newline_param(args, &i);
	while (args[i])
	{
		if (ft_putstr_fd(args[i++], 1) == -1)
		{
			perror("echo: write error");
			return (1);
		}
		if (args[i])
			write(1, " ", 1);
	}
	if (end_newline)
		write(1, "\n", 1);
	return (0);
}
