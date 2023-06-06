/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:57:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/06 14:01:43 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Create token list from command line passed as argument
Identifies special characters (|, ', ", <, <<, >, >>)
Mode :
0 = standard (interpreting everything)
1 = Single quote (interpreting nothing)
2 = double quote (interpreting nothing but $)
*/
void	lexer(t_data *data)
{
	t_tkn_lst	*tkn_lst;
	t_tkn_lst	*token;
	char		*cmd_l;

	tkn_lst = NULL;
	cmd_l = data->cmd_line;
	while (*cmd_l)
	{
		while (*cmd_l && ft_isspace(*cmd_l) && *cmd_l != '\n')
			cmd_l++;
		if (!*cmd_l)
			break ;
		token = tokenize(&cmd_l, data->env);
		if (!token)
			return (clear_token_list(&tkn_lst), (void)0);
		add_back_token(&tkn_lst, token);
		if (error_ambiguous(token, cmd_l, data))
			return (clear_token_list(&tkn_lst), (void)0);
	}
	if (!tkn_lst || last_token(tkn_lst)->type != END)
		add_back_token(&tkn_lst, new_token(0, END));
	data->token_list = tkn_lst;
}
