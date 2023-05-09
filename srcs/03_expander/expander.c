/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 12:17:54 by maaliber         ###   ########.fr       */
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

int	replace_content(t_tkn_lst *token, char *sub, int pos)
{
	int		offset;
	int		l;
	int		var_l;
	int		sub_l;
	char	*new;
	
	l = ft_strlen(token->content);
	var_l = word_len(&token->content[pos]);
	sub_l = ft_strlen(sub);
	offset = sub_l - var_l;
	new = malloc(l + offset + 1);
	if (!new)
		return(0);
	ft_memcpy(new, token->content, pos);
	ft_memcpy(new + pos, sub, sub_l);
	ft_memcpy(new + pos + sub_l, token->content + pos + var_l, l - pos - var_l);
	new[l + offset] = '\0';
	free(token->content);
	token->content = new;
	return (offset);
}

/*
Expand variable followed by $ in format by the corresponding value in env
• $ is not iterpreted when into single quote
*/
void	expand(t_tkn_lst *token, t_list *env)
{
	char	*to_find;
	char	*val;
	int		i;

	if (!token)
		return ;
	i = 0;
	while (i >= 0)
	{
		if (token->content[i] == '$')
		{
			to_find = cpy_word(&token->content[i + 1]);
			val = search_val(to_find, env);
			replace_content(token, val, i);
			free(to_find);
		}
		else
			i++;
		if (token->content[i] == '\0')
			i = -1;
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