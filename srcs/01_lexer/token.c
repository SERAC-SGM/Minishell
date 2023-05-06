/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 17:17:44 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Create standard token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
t_tkn_lst	*standard_token(char **str, t_list *env)
{
	t_tkn_lst	*token;
	int			ex;
	int			i;

	(void)env;
	ex = 0;
	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& !((*str)[i] == '\'' && ft_strchr((*str) + i + 1, '\''))
			&& !((*str)[i] == '\"' && ft_strchr((*str) + i + 1, '\"')))
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}
	if (!ft_isspace((*str)[i])
			&& !((*str)[i] == '\'' && ft_strchr((*str) + i + 1, '\''))
			&& !((*str)[i] == '\"' && ft_strchr((*str) + i + 1, '\"')))
		i++;
	token = new_token(ft_substr(*str, 0, i), 0);
	/*if (ex)
		expand_tokenize(token, env);*/
	*str += i;
	return (token);
}

/*
Create single quote token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
t_tkn_lst	*single_quote_token(char **str)
{
	t_tkn_lst	*token;
	int			i;

	i = 1;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	token = new_token(ft_substr(*str, 0, i), 1);
	trim_char(&token->content, '\'');
	*str += i + 1;
	return (token);
}

/*
Create double quote token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
t_tkn_lst	*double_quote_token(char **str, t_list *env)
{
	t_tkn_lst	*token;
	int			ex;
	int			i;

	(void)env;
	ex = 0;
	i = 1;
	while ((*str)[i] && (*str)[i] != '\"')
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}
	printf("ex=%d\n", ex);
	token = new_token(ft_substr(*str, 0, i), 2);
	trim_char(&token->content, '\"');
	if (ex)
		expand(token, env);
	*str += i + 1;
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
	int			len;

	len = ft_strlen(*str);
	if (len >= 2 && !ft_strncmp(*str, "<<", 2))
		return (*str += 2, new_token(0, HERE));
	if (len >= 2 && !ft_strncmp(*str, ">>", 2))
		return (*str += 2, new_token(0, APPEND));
	if (**str == '<')
		return (*str += 1, new_token(0, RD_IN));
	if (**str == '>')
		return (*str += 1, new_token(0, RD_OUT));
	if (**str == '|')
		return (*str += 1, new_token(0, PIPE));
	if (**str == '\n' || **str == '\0')
		return (*str += 1, new_token(0, END));
	return (NULL);
}

/*
Create token with command line with differents cases :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
t_tkn_lst	*generate_token(char **cmd_line, int mode, t_list *env)
{
	if (is_special(*cmd_line))
		return (special_token(cmd_line));
	if (mode == 0)
		return (standard_token(cmd_line, env));
	if (mode == 1)
		return (single_quote_token(cmd_line));
	if (mode == 2)
		return (double_quote_token(cmd_line, env));
	return (NULL);
}
