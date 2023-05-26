/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 15:50:10 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/26 17:54:10 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_len(char *str, int expander)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i] && !ft_isspace(str[i]))
	{
		if (expander && !isalnum(str[i]) && str[i] == '$')
			break ;
	}
	return (i);
}

char	*cpy_word(char *str)
{
	char	*word;
	int		len;

	len = word_len(str, 1);
	word = malloc((len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str, len + 1);
	return (word);
}
