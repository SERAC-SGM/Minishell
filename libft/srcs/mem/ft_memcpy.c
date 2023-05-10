/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:01:43 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 13:53:38 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst || !src) 
		return (NULL);
	if (dst == src)
		return (dst);
	while (n-- > 0)
		((unsigned char *)dst)[i++] = *(unsigned char *)src++;
	return (dst);
}
