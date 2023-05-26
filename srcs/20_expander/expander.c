/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/26 17:07:50 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Duplicates the ending non-alphanumeric characters.
*/
static char	*get_special_characters(char *content)
{
	int	i;

	i = 0;
	while (content[++i] && ft_isalnum(content[i]))
		;
	if (!content[i])
		return (NULL);
	return (ft_strdup(&content[i]));
}

/*
Replaces the content of the variable by its value. If non-alphanumeric
characters are present at the end, they are appened to the value.
*/
static void	replace_content(char **content, char *new_str, int pos)
{
	int		len_tot;
	int		len_init;
	int		len_new_str;
	char	*new;
	char	*special_characters;

	if (!*content)
		return ;
	special_characters = get_special_characters(*content);
	len_tot = ft_strlen(*content);
	len_init = word_len(&(*content)[pos], 1);
	len_new_str = ft_strlen(new_str);
	new = ft_calloc(len_tot + (len_new_str - len_init) + 1, sizeof(char));
	if (!new)
		return ;
	ft_memcpy(new + pos, new_str, len_new_str);
	free(*content);
	if (special_characters)
	{
		*content = ft_strjoin(new, special_characters);
		free(new);
	}
	else
		*content = new;
	free(special_characters);
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
		if ((*content)[i] == '$')
		{
			to_find = cpy_word(*content + i + 1);
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
