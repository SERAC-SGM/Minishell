/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:59:08 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 16:03:36 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "lexer.h"

t_tkn_lst	*new_token(char	*str, int type)
{
	t_tkn_lst	*token;

	if (!spec)
		return (NULL);
	token = malloc(sizeof(t_lst_arg));
	if (!token)
		return (NULL);
	token->content = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

t_tkn_lst	*last_token(t_tkn_lst *tk_list)
{
	if (!tk_list)
		return (NULL);
	while (tk_list->next)
		tk_list = tk_list->next;
	return (tk_list);
}

void	add_back_token(t_tkn_lst **tk_list, t_tkn_lst *token)
{
	t_tkn_lst	*tkn_last;

	if (!tk_list || !token)
		return ;
	if (!(*tk_list))
	{
		(*tk_list) = token;
		return ;
	}
	tkn_last = ft_lstlast_arg(*tk_list);
	tkn_last->next = token;
}

void	del1_token(t_tkn_lst *token)
{
	if (!token)
		return ;
	free(token->str);
	token->str = NULL;
	token->type = 0;
	free(token);
}

void	clear_token_list(t_tkn_lst **tk_list)
{
	t_tkn_lst	*tk_next;

	if (!tk_list)
		return ;
	while (*tk_list)
	{
		tk_next = (*tk_list)->next;
		ft_lstdelone_arg(*tk_list);
		*tk_list = tk_next;
	}
}
