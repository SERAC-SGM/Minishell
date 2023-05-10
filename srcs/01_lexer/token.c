/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 12:38:55 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Create special token with NULL content and type :
• RD_IN
• HERE
• RD_OUT
• APPEND
• PIPE
*/
t_tkn_lst	*special_token(char **str)
{
	int			len;

	len = ft_strlen(*str);
	if (len >= 2 && !ft_strncmp(*str, "<<", 2))
		return (*str += 2, new_token(0, HERE));
	if (len >= 2 && !ft_strncmp(*str, ">>", 2))
		return (*str += 2, new_token(0, APPEND));
	if (**str == '<')
		return (*str += 1, new_token(0, RD_IN));
	if (**str == '>')
		return (*str += 1, new_token(0, RD_OUT));
	if (**str == '|')
		return (*str += 1, new_token(0, PIPE));
	if (**str == '\n' || **str == '\0')
		return (*str += 1, new_token(0, END));
	return (NULL);
}

t_tkn_lst	*split_input(char **prev, char **next)
{
	
}

/*
Create token with command line with differents cases :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
t_tkn_lst	*tokenize(char **cmd_line, t_list *env)
{
	t_tkn_lst	*tkn_list;
	t_tkn_lst	*sub_list;
	char		*add;
	char		*store;
	int			mode;

	if (is_special(*cmd_line))
		return (special_token(cmd_line));
	tkn_list = NULL;
	store = NULL;
	while (!ft_isspace(**cmd_line) && !is_special(*cmd_line))
	{
		mode = set_mode(*cmd_line);
		if (mode == 0)
		{
			add = standard_mode(cmd_line, env);
			sub_list = split_input(&add, &store);
		}
		if (mode == 1)
			store = ft_strjoin_free(store, single_quote_mode(cmd_line));
		if (mode == 2)
			store = ft_strjoin_free(store, double_quote_mode(cmd_line, env));
		if (sub_list)
			add_back_token(&tkn_list, sub_list);
	}
	add_back_token(&tkn_list, new_token(store, 0));
	return (tkn_list);
}
