/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:13 by matnam            #+#    #+#             */
/*   Updated: 2023/06/04 22:31:23 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parsing_error_msg(int token_type)
{
	ft_putstr_fd("syntax error near unexpected token `", 2);
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
	g_sig.error_status = 2;
}

int	parsing_error(t_tkn_lst *token)
{
	(void)token;
	if (token->type == PIPE)
		return (parsing_error_msg(token->type), 1);
	while (token->type != END)
	{
		if (token->type != STD && token->next->type != STD)
			return (parsing_error_msg(token->next->type), 1);
		token = token->next;		
	}
	return (0); 
}
