/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:39:31 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/19 14:01:48 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*nlast;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	nlast = ft_lstlast(*lst);
	nlast->next = new;
}

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	free(lst->line);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*nnext;

	if (!lst)
		return ;
	while (*lst)
	{
		nnext = (*lst)->next;
		ft_lstdelone(*lst);
		*lst = nnext;
	}
}
