/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/05 14:52:21 by maaliber         ###   ########.fr       */
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
			&& (*str)[i] != '\'' && (*str)[i] != '\"')
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}	
	token = new_token(ft_substr(*str, 0, i), 0);
	/*if (ex)
		token = expander(token, env);*/
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

	i = 0;
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
	i = 0;
	while ((*str)[i] && (*str)[i] != '\"')
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}
	token = new_token(ft_substr(*str, 0, i), 2);
	trim_char(&token->content, '\"');
	/*if (ex)
		token = expander(token, env);*/
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
	t_tkn_lst	*token;
	int			len;

	len = ft_strlen(*str);
	if (len >= 2 && !ft_strncmp(*str, "<<", 2))
	{
		token = new_token(0, HERE);
		(*str)++;
	}
	if (len >= 2 && !ft_strncmp(*str, ">>", 2))
	{
		token = new_token(0, APPEND);
		(*str)++;
	}
	if (**str == '<')
		token = new_token(0, RD_IN);
	if (**str == '>')
		token = new_token(0, RD_OUT);
	if (**str == '|')
		token = new_token(0, PIPE);
	*str += 1;
	return (0);
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
	t_tkn_lst	*token;

	if (is_special(*cmd_line))
	{	token = special_token(cmd_line);
		printf("%s-mode [%d]\n", token->content, mode);}
	if (mode == 0)
	{	token = standard_token(cmd_line, env);
		printf("%s-mode [%d]\n", token->content, mode);}
	if (mode == 1)
	{	token = single_quote_token(cmd_line);
		printf("%s-mode [%d]\n", token->content, mode);
	}
	if (mode == 2)
	{	token = double_quote_token(cmd_line, env);
		printf("%s-mode [%d]\n", token->content, mode);}
	return (token);
}
