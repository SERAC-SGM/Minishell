/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ft2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 12:39:31 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 12:53:40 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Basic fonctions for list
• Add element at the end of list
• Delete one element
• Clear list
*/
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
