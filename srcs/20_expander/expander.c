/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/06 11:23:43 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the variable length delimited by spaces, 
non alphanumeric or underscores characters 
*/
static int	var_len(char *str)
{
	int	i;

	i = 1;
	if (!str)
		return (0);
	if (ft_isdigit(str[1]) || str[1] == '?')
		return (2);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*cpy_var(char *str)
{
	char	*word;
	int		len;

	len = var_len(str);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, len + 1);
	return (word);
}

/*
Replaces the content of the variable by its value. If non-alphanumeric
characters are present at the end, they are appened to the value.
*/
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
	var_l = var_len(&(*content)[pos]);
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
Expand variable followed by $ in format by the corresponding valueue in env
• $ is not iterpreted when into single quote
*/
void	expand(char **content, t_list *env)
{
	char	*to_find;
	char	*value;
	int		i;

	if (!*content)
		return ;
	i = 0;
	while ((*content)[i])
	{
		if ((*content)[i] == '$' && (*content)[i + 1]
			&& (ft_isalnum((*content)[i + 1]) || (*content)[i + 1] == '?'))
		{
			to_find = cpy_var(*content + i + 1);
			if (ft_strcmp(to_find, "?") == 0)
				value = ft_itoa(g_sig.error_status);
			else
				value = get_var_value(to_find, env);
			replace_content(content, value, i);
			if (ft_strcmp(to_find, "?") == 0)
				free(value);
			free(to_find);
		}
		else
			i++;
	}
}
