/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:59:08 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 19:02:16 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Allocates (with malloc) a new token list.
• content: string
• type:    
*/
t_tkn_lst	*new_token(char	*str, int type)
{
	t_tkn_lst	*token;

	token = malloc(sizeof(t_tkn_lst));
	if (!token)
		return (NULL);
	token->content = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

/*
Get last token of the list
*/
t_tkn_lst	*last_token(t_tkn_lst *tk_list)
{
	if (!tk_list)
		return (NULL);
	while (tk_list->next)
		tk_list = tk_list->next;
	return (tk_list);
}

/*
Add a token or a token list at the end of an existing list,
if existing list is NULL return the list added
*/
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
	tkn_last = last_token(*tk_list);
	tkn_last->next = token;
}

/*
Delete 1 token
*/
void	del1_token(t_tkn_lst *token)
{
	if (!token)
		return ;
	free(token->content);
	token->content = NULL;
	token->type = 0;
	free(token);
}

/*
Free and delete all content of the list
*/
void	clear_token_list(t_tkn_lst **tk_list)
{
	t_tkn_lst	*tk_next;

	if (!tk_list)
		return ;
	while (*tk_list)
	{
		tk_next = (*tk_list)->next;
		del1_token(*tk_list);
		*tk_list = tk_next;
	}
}
