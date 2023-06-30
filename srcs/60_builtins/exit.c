/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:53:26 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/30 13:42:54 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_number(char *arg)
{
	int	s;

	s = 1;
	if (*arg == '+' || *arg == '-')
	{
		if (*arg == '-')
			s = 0;
		arg++;
	}
	if (!ft_isdigit(*arg))
		return (0);
	while (*arg == '0')
		arg++;
	if (ft_strlen(arg) > 10)
		return (0);
	if ((s && ft_strlen(arg) == 10
			&& ft_strncmp(arg, "2147483647", 11) > 0)
		|| (!s && ft_strlen(arg) == 10
			&& ft_strncmp(arg, "2147483648", 11) > 0))
		return (0);
	while (*arg && ft_isdigit(*arg))
		arg++;
	if (*arg != '\0')
		return (0);
	return (1);
}

int	ft_exit(char **args)
{
	if (args[2])
		return (error_msg_cmd(E_TOO_MANY_ARG, "exit: ", NULL), 1);
	g_sig.exit = 1;
	if (args[1])
	{
		if (!is_number(args[1]))
			return (error_msg_cmd(E_NUMERIC_ARG, "exit: ", args[1]), 2);
		return (ft_atoi(args[1]));
	}
	g_sig.error_status = g_sig.exit_status;
	return (g_sig.error_status);
}
