/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_mode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 19:04:17 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/13 12:45:26 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_mode(char *cmd_l)
{
	if (*cmd_l == '\'' && ft_strchr(cmd_l + 1, '\''))
		return (1);
	if (*cmd_l == '\"' && ft_strchr(cmd_l + 1, '\"'))
		return (2);
	return (0);
}

char	*standard_mode(char **str, t_list *env)
{
	char	*content;
	int		expander_flag;
	int		i;

	expander_flag = 0;
	i = 0;
	while ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& !((*str)[i] == '\'' && ft_strchr((*str) + i + 1, '\''))
			&& !((*str)[i] == '\"' && ft_strchr((*str) + i + 1, '\"')))
	{
		if ((*str)[i] == '$')
			expander_flag = 1;
		i++;
	}
	if ((*str)[i] && !ft_isspace((*str)[i]) && !is_special((*str) + i)
			&& !((*str)[i] == '\'' && ft_strchr((*str) + i + 1, '\''))
			&& !((*str)[i] == '\"' && ft_strchr((*str) + i + 1, '\"')))
		i++;
	content = ft_substr(*str, 0, i);
	if (expander_flag)
		expand(&content, env);
	*str += i;
	return (content);
}

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

char	*double_quote_mode(char **str, t_list *env)
{
	char	*content;
	int		expander_flag;
	int		i;

	expander_flag = 0;
	i = 1;
	while ((*str)[i] && (*str)[i] != '\"')
	{
		if ((*str)[i] == '$')
			expander_flag = 1;
		i++;
	}
	content = ft_substr(*str, 0, i);
	trim_char(&content, '\"');
	if (expander_flag)
		expand(&content, env);
	*str += i + 1;
	return (content);
}
