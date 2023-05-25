/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/25 14:30:08 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_special_character(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (0);
	return (1);
}

int	word_len(char *str, int expander)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i] && !ft_isspace(str[i]))
	{
		if (expander && is_special_character(str[i])) // pas fini mais là g la flemme
			break ;
	}
	return (i);
}

/*
Duplicates (with malloc) the string passed as argument.
*/
static char	*cpy_word(char *str)
{
	char	*word;
	int		l;

	l = word_len(str, 1);
	word = malloc((l + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, l + 1);
	return (word);
}

//faut garder les caractères spéciaux à la fin mais comme dit plus haut là j'ai la flemme je suis en pleine digestion il fait beau il fait chaud j'ai envie de me casser putain il est que 14h29 j'ai qu'une hâte c'est de me barrer de cette école ET PUTAIN ALLUMEZ LA CLIM
static void	replace_content(char **content, char *sub, int pos)
{
	int		len;
	int		var_l;
	int		sub_l;
	int		offset;
	char	*new;

	if (!*content)
		return ;
	len = ft_strlen(*content);
	var_l = word_len(&(*content)[pos], 1);
	sub_l = ft_strlen(sub);
	offset = sub_l - var_l;
	new = ft_calloc(len + offset + 1, sizeof(char));
	if (!new)
		return ;
	ft_memcpy(new, *content, pos);
	ft_memcpy(new + pos, sub, sub_l);
	ft_memcpy(new + pos + sub_l, *content + pos + var_l, len - pos - var_l);
	free(*content);
	*content = new;
}

/*
Expand variable followed by $ in format by the corresponding value in env
• $ is not iterpreted when into single quote
*/
void	expand(char **content, t_list *env, t_list *set)
{
	char	*to_find;
	char	*val;
	int		i;

	(void)set;
	if (!*content)
		return ;
	i = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '$')
		{
			to_find = cpy_word(*content + i + 1);
			if (ft_strcmp(to_find, "?") == 0)
				val = ft_itoa(g_sig.error_status);
			else
				val = get_var_value(to_find, env);
			replace_content(content, val, i);
			free(to_find);
			if (ft_strcmp(to_find, "?") == 0)
				free(val);
		}
		else
			i++;
	}
}
