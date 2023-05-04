/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:57:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 15:31:58 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Checks if the string corresponds to any special character and returns the
matching value:
• <:  returns RD_IN
• <<: returns HERE
• >:  returns RD_OUT
• >>: returns APPEND
• |:  returns PIPE
• returns 0 otherwise
*/
int	is_special(char *str)
{
	int		l;

	l = ft_strlen(str);
	if (l >= 2 && !ft_strncmp(str, "<<", 2))
		return (HERE);
	if (l >= 2 && !ft_strncmp(str, ">>", 2))
		return (APPEND);
	if (*str == '<')
		return (RD_IN);
	if (*str == '>')
		return (RD_OUT);
	if (*str == '|')
		return (PIPE);
	return (0);
}

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
	cmd_l = data->cmd_line;
	while (cmd_l)
	{
		token = generate_token(&cmd_l, mode, data->env);
		if (!token)
			return (clear_token_list(tkn_lst), 0);
		add_back_token(tkn_lst, token);	
	}
}
