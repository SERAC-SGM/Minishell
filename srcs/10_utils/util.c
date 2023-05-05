/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:18:43 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/05 12:03:36 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_char(char **str, char c)
{
	char	*rst;
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(*str);
	if (*str)
		return ;
	if (*str[0] == c)
		start++;
	if (*str[end] == c)
		end--;
	rst = malloc((end - start + 1) * sizeof(char));
	if (!rst)
		return (free(*str), *str = 0, (void)0);
	ft_strlcpy(rst, *str + start, end - start);
	rst[end - start] = '\0';
	return (free(*str), *str = rst, (void)0);
}
