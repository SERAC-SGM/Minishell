/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 17:58:32 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Create special token with NULL content and type :
• RD_IN
• HERE
• RD_OUT
• APPEND
• PIPE
*/
static t_tkn_lst	*special_token(char **str)
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

/*
Split string into token with in standard mode input [0]
• concatenate previous [store] input with current input
• create a token if one or several spaces are identified after expanding content
• change stored input with the rest of the input
*/
static t_tkn_lst	*split_input(char **store, char *add)
{
	t_tkn_lst	*tkn_list;
	char		*content;
	int			wrd_l;

	tkn_list = NULL;
	while (*add)
	{
		wrd_l = word_len(add);
		if ((size_t)wrd_l == ft_strlen(add))
			return (*store = ft_strjoin_dup1(*store, add), tkn_list);
		content = ft_calloc(ft_strlen(*store) + wrd_l + 1, sizeof(char));
		if (!content)
			return (tkn_list);
		ft_memcpy(content, *store, ft_strlen(*store));
		ft_memcpy(content + ft_strlen(*store), add, wrd_l);
		free(*store);
		*store = NULL;
		add_back_token(&tkn_list, new_token(content, 0));
		add += wrd_l;
		while (ft_isspace(*add))
			add++;
	}
	return (tkn_list);
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
	char		*add;
	char		*store;

	if (is_special(*cmd_line))
		return (special_token(cmd_line));
	tkn_list = NULL;
	store = NULL;
	while (!ft_isspace(**cmd_line) && !is_special(*cmd_line))
	{
		if (set_mode(*cmd_line) == 0)
		{
			add = standard_mode(cmd_line, env);
			add_back_token(&tkn_list, split_input(&store, add));
			free(add);
		}
		else if (set_mode(*cmd_line) == 1)
			store = ft_strjoin_free(store, single_quote_mode(cmd_line));
		else if (set_mode(*cmd_line) == 2)
			store = ft_strjoin_free(store, double_quote_mode(cmd_line, env));
	}
	if (store)
		add_back_token(&tkn_list, new_token(store, 0));
	return (tkn_list);
}
