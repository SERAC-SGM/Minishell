/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:57:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 12:40:32 by maaliber         ###   ########.fr       */
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
• \n or \0: returns END
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
	if (*str == '\0' || *str == '\n')
		return (END);
	return (0);
}

/*
Set mode - return value of mode used for generating token
• 1 if the first character is ' and ' is not unclosed
• 2 if the first character is " and " is not unclosed
• 0 otherwise
*/
int	set_mode(char *cmd_l)
{
	if (*cmd_l == '\'' && ft_strchr(cmd_l + 1, '\''))
		return (1);
	if (*cmd_l == '\"' && ft_strchr(cmd_l + 1, '\"'))
		return (2);
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
	while (*cmd_l)
	{
		while (*cmd_l && ft_isspace(*cmd_l))
			cmd_l++;
		mode = set_mode(cmd_l);
		token = generate_token(&cmd_l, mode, data->env);
		if (!token)
			return (clear_token_list(&tkn_lst), NULL);
		add_back_token(&tkn_lst, token);
	}
	return (tkn_lst);
}
