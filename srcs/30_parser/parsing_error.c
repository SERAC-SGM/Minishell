/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:13 by matnam            #+#    #+#             */
/*   Updated: 2023/06/04 18:30:37 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_error_msg(int token_type)
{
	(void)token_type;
}

int	parsing_error(t_tkn_lst *token)
{
	(void)token;
	if (token->type == PIPE)
		return (parsing_error_msg(token->type), 1);
	while (token->type != END)
	{
		if (token->type != STD && token->next->type != STD)
			return (parsing_error_msg(token->type), 1);
		token = token->next;		
	}
	return (0); 
}
