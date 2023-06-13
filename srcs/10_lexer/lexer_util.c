/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:58:47 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/13 12:30:57 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char *str)
{
	int		l;

	if (!str)
		return (END);
	l = ft_strlen(str);
	if (l >= 2)
	{
		if (!ft_strncmp(str, "<<", 2))
			return (HERE);
		if (!ft_strncmp(str, ">>", 2))
			return (APPEND);
	}
	if (*str == '<')
		return (RD_IN);
	if (*str == '>')
		return (RD_OUT);
	if (*str == '|')
		return (PIPE);
	if (*str == '\0' || *str == '\n')
		return (END);
	return (0);
}
