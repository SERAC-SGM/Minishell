/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:04:17 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 12:34:56 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Create standard token :
• if it starts with a special character : |, <, <<, >, >>
• if it's a standard entry : mode 0
• if it's in between single quote ['] : mode 1
• if it's in between double quote ["] : mode 2
*/
char	*standard_mode(char **str, t_list *env)
{
	char	*content;
	int		ex;
	int		i;

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
	content = ft_substr(*str, 0, i);
	if (ex)
		expand(&content, env);
	*str += i;
	return (content);
}

/*
Create single quote token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
char	*single_quote_mode(char **str)
{
	char	*content;
	int		i;

	i = 1;
	while ((*str)[i] && (*str)[i] != '\'')
		i++;
	content = ft_substr(*str, 0, i);
	trim_char(&content, '\'');
	*str += i + 1;
	return (content);
}

/*
Create double quote token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
char	*double_quote_mode(char **str, t_list *env)
{
	char	*content;
	int		ex;
	int		i;

	(void)env;
	ex = 0;
	i = 1;
	while ((*str)[i] && (*str)[i] != '\"')
	{
		if ((*str)[i] == '$')
			ex = 1;
		i++;
	}
	content = ft_substr(*str, 0, i);
	trim_char(&content, '\"');
	if (ex)
		expand(&content, env);
	*str += i + 1;
	return (content);
}
