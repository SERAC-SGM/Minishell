/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:57:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 16:56:05 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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
	if (*str == ';')
		return (SEMICOLON);
	return (0);
}

t_tkn_lst	*lexer(char *cmd_line)
{
	t_tkn_lst	*tkn_lst;
	t_tkn_lst	*token;
	int			mode; //0 = standard (interpreting everything), 1 = Single quote (interpreting nothing), 2 = double quote (interpreting nothing but $)

	tkn_lst = NULL;
	mode = 0;
	while (*cmd_line)
	{
		if (is_special(cmd_line))
			token = special_token(cmd_line);
		else
			token = generate_token(cmd_line, mode);
		if (!token)
			return (clear_token_list(tkn_lst), 0);
		add_back_token(tkn_lst, token);	
	}
}
