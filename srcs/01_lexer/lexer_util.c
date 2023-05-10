/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:58:47 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 15:20:41 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if the string corresponds to any special character and returns the
matching value:
• <:  returns RD_IN
• <<: returns HERE
• >:  returns RD_OUT
• >>: returns APPEND
• |:  returns PIPE
• \n or \0: returns END
• returns 0 otherwise
*/
int	is_special(char *str)
{
	int		l;

	l = ft_strlen(str);
	if (l >= 2 && !ft_strncmp(str, "<<", 2))
		return (HERE);
	if (l >= 2 && !ft_strncmp(str, ">>", 2))
		return (APPEND);
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
