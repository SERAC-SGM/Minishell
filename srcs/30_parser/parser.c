/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/30 13:35:59 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the size of the command (name + optional arguments).
*/
static int	get_cmd_size(t_tkn_lst *token)
{
	int	size;

	size = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == RD_IN || token->type == HERE
			|| token->type == RD_OUT || token->type == APPEND)
			size--;
		else
			size++;
		token = token->next;
	}
	return (size);
}

/*
Adds a new command in the data structure. The first token is used as the name of
the command, and all following non-special tokens as optional arguments.
Returns the next special token.
*/
static void	add_attribute(t_tkn_lst *token, t_data *data, int proc_idx)
{
	int	i;
	int	size;

	size = get_cmd_size(token);
	if (!data->cmds_tab[proc_idx].args)
	{
		data->cmds_tab[proc_idx].args = ft_calloc(size + 1, sizeof(char *));
		if (!data->cmds_tab[proc_idx].args)
			return (error_msg(E_MEM, NULL), (void)0);
	}
	i = tab_size(data->cmds_tab[proc_idx].args);
	if (i == 0)
	{
		data->cmds_tab[proc_idx].args[i] = ft_strdup(token->content);
		if (!data->cmds_tab[proc_idx].args[i])
			return (error_msg(E_MEM, NULL), (void)0);
		data->cmds_tab[proc_idx].name = token->content;
	}
	else
		data->cmds_tab[proc_idx].args[i] = token->content;
	data->cmds_tab[proc_idx].arg_count = i;
	data->cmds_tab[proc_idx].process_index = proc_idx;
}

static t_tkn_lst	*parse_type(t_data *data, t_tkn_lst *token, int *proc_idx)
{
	if (token->type == PIPE)
	{
		token = token->next;
		data->process_nb++;
		++*proc_idx;
		init_cmd(&data->cmds_tab[*proc_idx]);
		data->cmds_tab[*proc_idx].process_index = *proc_idx;
	}
	if (token->type == STD)
	{
		add_attribute(token, data, *proc_idx);
		token = token->next;
	}
	if (token->type != END && !token->content && token->type != PIPE)
	{	
		redirection(token, &data->cmds_tab[*proc_idx], data, 0);
		token = token->next->next;
	}
	if (g_sig.error_status == 130)
		return (NULL);
	return (token);
}

int	parser(t_data *data)
{
	t_tkn_lst	*token;
	int			proc_idx;

	g_sig.exit_status = g_sig.error_status;
	g_sig.error_status = 0;
	if (!data->token_list || parsing_error(data->token_list))
		return (0);
	proc_idx = 0;
	token = data->token_list;
	init_cmd(&data->cmds_tab[0]);
	data->cmds_tab[0].process_index = 0;
	while (token->type != END)
	{
		token = parse_type(data, token, &proc_idx);
		if (!token)
			return (0);
	}
	return (1);
}
