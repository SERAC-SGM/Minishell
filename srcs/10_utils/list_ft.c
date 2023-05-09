/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:39:31 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 13:06:17 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Basic fonctions for list
• Create node
• Get last node
• Add element at the end of list
• Delete one element
• Clear list
*/
t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->line = content;
	node->next = NULL;
	return (node);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

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
