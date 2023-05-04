/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 15:37:36 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn_lst	*standard_token(char **str, t_list *env)
{
	int		i;
	char	*token;
	int		ex;

	i = 0;
	ex = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& (*str)[i] != '\'' && (*str)[i] != '"')
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}	
	token = new_token(ft_substr(*str, 0, i), 0);
	trim_token(token, "\f\n\r\t\v ");
	if (ex)
		token = expander(token, env);
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
	trim_token(token, "\'");
	*str += i;
	return (token);
}

t_tkn_lst	*double_quote_token(char **str, t_list *env)
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
	trim_token(token, "\"");
	if (ex)
		token = expander(token, env);
	*str += i;
	return (token);
}

/*
Create special token with NULL content and type :
• RD_IN
• HERE
• RD_OUT
• APPEND
• PIPE
*/
t_tkn_lst	*special_token(char **str)
{
	t_tkn_lst	*token;
	int			length;

	length = ft_strlen(str);
	if (length >= 2 && !ft_strncmp(str, "<<", 2))
	{
		token = new_token(0, HERE);
		(*str)++;
	}
	if (length >= 2 && !ft_strncmp(str, ">>", 2))
	{
		token = new_token(0, APPEND);
		(*str)++;
	}
	if (*str == '<')
		token = new_token(0, RD_IN);
	if (*str == '>')
		token = new_token(0, RD_OUT);
	if (*str == '|')
		token = new_token(0, PIPE);
	*str++;
	return (0);
}

/*
Generate token from command line with differents cases :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
t_tkn_lst	*generate_token(char **cmd_line, int mode, t_list *env)
{
	int		i;
	char	*token;

	if (is_special(*cmd_line))
		token = special_token(cmd_line);
	if (mode == 0)
		token = standard_token(cmd_line, env);
	if (mode == 1)
		token = single_quote_token(cmd_line);
	if (mode == 2)
		token = double_quote_token(cmd_line, env);
	return (token);
}
