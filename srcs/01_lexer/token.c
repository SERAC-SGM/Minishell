/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 14:04:24 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_tkn_lst	*standard_token(char **str)
{
	int		i;
	char	*token;

	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& (*str)[i] != '\'' && (*str)[i] != '"' && (*str)[i] != '$')
		i++;
	token = new_token(ft_substr(*str, 0, i), 0);
	*str += i;
	return (token);
}

t_tkn_lst	*single_quote_token(char **str)
{
	int		i;
	char	*token;

	i = 0;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	token = new_token(ft_substr(*str, 0, i), 1);
	*str += i;
	return (token);
}

t_tkn_lst	*double_quote_token(char **str)
{
	int		i;
	char	*token;
	int		ex;

	i = 0;
	ex = 0;
	while ((*str)[i] && (*str)[i] != '"')
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}
	token = new_token(ft_substr(*str, 0, i), 2);
	if (ex)
		token = expander(token);
	*str += i;
	return (token);
}

t_tkn_lst	*generate_token(char **cmd_line, int mode)
{
	int		i;
	char	*token;

	if (mode == 0)
		token = standard_token(cmd_line);
	if (mode == 1)
		token = single_quote_token(cmd_line);
	if (mode == 2)
		token = double_quote_token(cmd_line);
	return (token);
}


t_tkn_lst	*special_token(char **str)
{
	t_tkn_lst	*token;
	int			length;

	length = ft_strlen(str);
	if (length >= 2 && !ft_strncmp(str, "<<", 2))
	{
		token = new_token(0, 11);
		(*str)++;
	}
	if (length >= 2 && !ft_strncmp(str, ">>", 2))
	{
		token = new_token(0, 12);
		(*str)++;
	}
	if (*str == '<')
		token = new_token(0, 13);
	if (*str == '>')
		token = new_token(0, 14);
	if (*str == '|')
		token = new_token(0, 15);
	*str++;
	return (0);
}
