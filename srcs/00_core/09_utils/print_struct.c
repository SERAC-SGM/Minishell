/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:56:50 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 15:34:56 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_tkn_lst *lex)
{
	while (lex)
	{
		printf("type:[%d] | content: [%s]\n", lex->type, lex->content);
		lex = lex->next;
	}
}

void	print_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}
