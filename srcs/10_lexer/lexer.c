/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:57:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/01 13:01:39 by matnam           ###   ########.fr       */
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
t_tkn_lst	*lexer(t_data *data)
{
	t_tkn_lst	*tkn_lst;
	t_tkn_lst	*token;
	char		*cmd_l;

	tkn_lst = NULL;
	if (!data->cmd_line)
		return (new_token(0, END));
	cmd_l = data->cmd_line;
	while (*cmd_l)
	{
		while (*cmd_l && ft_isspace(*cmd_l) && *cmd_l != '\n')
			cmd_l++;
		if (!*cmd_l)
			break ;
		token = tokenize(&cmd_l, data->env, data->set);
		if (!token)
			return (clear_token_list(&tkn_lst), NULL);
		add_back_token(&tkn_lst, token);
	}
	if (!tkn_lst || last_token(tkn_lst)->type != END)
		add_back_token(&tkn_lst, new_token(0, END));
	return (tkn_lst);
}
