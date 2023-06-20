/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:18:43 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/13 12:50:43 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_char(char **str, char c)
{
	char	*rst;
	int		start;
	int		end;

	(void)c;
	start = 0;
	end = ft_strlen(*str);
	if (!*str)
		return ;
	while ((*str)[start] == c)
		start++;
	while (end > start && (*str)[end] == c)
		end--;
	rst = malloc((end - start + 1) * sizeof(char));
	if (!rst)
		return (free(*str), *str = 0, (void)0);
	ft_strlcpy(rst, *str + start, end - start + 1);
	return (free(*str), *str = rst, (void)0);
}

char	*ft_strjoin_dup1(char *s1, char *s2)
{
	char	*rst;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	rst = ft_strjoin(s1, s2);
	return (free(s1), rst);
}

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

char	**env_to_tab(t_list	*env)
{
	char	**env_tab;
	int		i;

	env_tab = malloc((ft_lstsize(env) + 1) * sizeof(char *));
	if (!env_tab)
		return (error_msg(E_MEM, NULL), NULL);
	i = 0;
	while (env)
	{
		env_tab[i++] = env->line;
		env = env->next;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
