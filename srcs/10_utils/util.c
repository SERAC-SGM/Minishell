/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:18:43 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 12:11:08 by maaliber         ###   ########.fr       */
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
