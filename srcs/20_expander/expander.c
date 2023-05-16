/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 16:03:20 by lletourn         ###   ########.fr       */
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

void	replace_content(char **content, char *sub, int pos)
{
	int		l;
	int		var_l;
	int		sub_l;
	int		offset;
	char	*new;

	if (!*content)
		return ;
	l = ft_strlen(*content);
	var_l = word_len(&(*content)[pos]);
	sub_l = ft_strlen(sub);
	offset = sub_l - var_l;
	new = ft_calloc(l + offset + 1, sizeof(char));
	if (!new)
		return ;
	ft_memcpy(new, *content, pos);
	ft_memcpy(new + pos, sub, sub_l);
	ft_memcpy(new + pos + sub_l, *content + pos + var_l, l - pos - var_l);
	free(*content);
	*content = new;
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
			replace_content(content, val, i);
			free(to_find);
		}
		else
			i++;
	}
	return ;
}
