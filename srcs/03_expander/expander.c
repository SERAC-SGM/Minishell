/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 14:14:51 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

char	*cpy_word(char *str)
{
	char	*word;
	int		l;

	l = word_len(str);
	word = malloc((l + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, l + 1);
	return (word);
}

int	replace_content(char **content, char *sub, int pos)
{
	int		offset;
	int		l;
	int		var_l;
	int		sub_l;
	char	*new;

	if (!*content)
		return (0);
	l = ft_strlen(*content);
	var_l = word_len(&(*content)[pos]);
	sub_l = ft_strlen(sub);
	offset = sub_l - var_l;
	new = ft_calloc(l + offset + 1, sizeof(char));
	if (!new)
		return (0);
	ft_memcpy(new, *content, pos);
	ft_memcpy(new + pos, sub, sub_l);
	ft_memcpy(new + pos + sub_l, *content + pos + var_l, l - pos - var_l);
	free(*content);
	*content = new;
	return (offset);
}

/*
Expand variable followed by $ in format by the corresponding value in env
• $ is not iterpreted when into single quote
*/
void	expand(char **content, t_list *env)
{
	char	*to_find;
	char	*val;
	int		i;

	if (!*content)
		return ;
	i = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '$')
		{
			to_find = cpy_word(*content + i + 1);
			val = get_var_value(to_find, env);
			i += replace_content(content, val, i);
			free(to_find);
		}
		else
			i++;
	}
	return ;
}

/*
Expand variable followed by $ in format by the corresponding value in env
• $ is not iterpreted when into single quote
*/
/*void	expand_tokenize(t_tkn_lst *token, t_list *env)
{
	if (!token)
		return ;
	expand(token, env);
	
	return ;
}
*/
