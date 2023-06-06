/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:54:54 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/06 11:50:34 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the word length (delimited by spaces).
*/
static int	word_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

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

	if (!*str || **str == '\0')
		return (new_token(0, END));
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
	if (**str == '\n')
		return (*str += 1, new_token(0, END));
	return (NULL);
}

/*
Split string into token with in standard mode input [0]
• concatenate previous [store] input with current input
• create a token if one or several spaces are identified after expanding content
• change stored input with the rest of the input
*/
t_tkn_lst	*split_input(char **store, char *add)
{
	t_tkn_lst	*tkn_list;
	char		*content;
	int			wrd_l;

	if (!*add && !*store)
		return (new_token(ft_strdup(""), STD));
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
		add_back_token(&tkn_list, new_token(content, STD));
		add += wrd_l;
		while (ft_isspace(*add))
			add++;
	}
	return (tkn_list);
}

/*
Creates token with command line with differents cases :
• if it starts with a special character : |, <, <<, >, >>
• if it's a standard entry : mode 0
• if it's between single quote ['] : mode 1
• if it's between double quote ["] : mode 2
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
			store = ft_strjoin_free(store,
					double_quote_mode(cmd_line, env));
	}
	if (store)
		add_back_token(&tkn_list, new_token(store, STD));
	return (tkn_list);
}
