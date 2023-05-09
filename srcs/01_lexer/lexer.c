/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:57:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 17:08:40 by maaliber         ###   ########.fr       */
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
	int			mode;

	tkn_lst = NULL;
	mode = 0;
	if (!data->cmd_line)
		return (NULL);
	cmd_l = data->cmd_line;
	while (*cmd_l)
	{
		while (*cmd_l && ft_isspace(*cmd_l) && *cmd_l != '\n')
			cmd_l++;
		token = tokenize(&cmd_l, data->env);
		if (!token)
			return (clear_token_list(&tkn_lst), NULL);
		add_back_token(&tkn_lst, token);
	}
	return (tkn_lst);
}
