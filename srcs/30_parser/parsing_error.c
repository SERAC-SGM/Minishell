/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:13 by matnam            #+#    #+#             */
/*   Updated: 2023/06/27 11:19:02 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	token_error_msg(int token_type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token_type == PIPE)
		ft_putstr_fd("|'\n", 2);
	if (token_type == RD_IN)
		ft_putstr_fd("<'\n", 2);
	if (token_type == HERE)
		ft_putstr_fd("<<'\n", 2);
	if (token_type == RD_OUT)
		ft_putstr_fd(">'\n", 2);
	if (token_type == APPEND)
		ft_putstr_fd(">>'\n", 2);
	if (token_type == END)
		ft_putstr_fd("newline'\n", 2);
}

int	parsing_error(t_tkn_lst *token)
{
	if (token->type == PIPE)
	{
		token_error_msg(token->type);
		g_sig.error_status = 2;
		return (1);
	}
	while (token->type != END)
	{
		if (token->type != STD && token->next->type != STD)
		{
			if (token->type != PIPE || (token->type == PIPE
					&& (token->next->type == PIPE || token->next->type == END)))
			{
				token_error_msg(token->next->type);
				g_sig.error_status = 2;
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}
