/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/25 12:23:42 by lletourn         ###   ########.fr       */
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
			return (error_msg(E_MEM, NULL, data), (void)0);
	}
	i = tab_size(data->cmds_tab[proc_idx].args);
	if (i == 0)
	{
		data->cmds_tab[proc_idx].args[i] = ft_strdup(token->content);
		if (!data->cmds_tab[proc_idx].args[i])
			return (error_msg(E_MEM, NULL, data), (void)0);
		data->cmds_tab[proc_idx].name = token->content;
	}
	else
		data->cmds_tab[proc_idx].args[i] = token->content;
	data->cmds_tab[proc_idx].arg_count = i;
	data->cmds_tab[proc_idx].process_index = proc_idx;
}

/*
When encountering a redirection token (< << > >>), assings the correct
following filename to the command structure.
Returns the next token after the filename.
If no filemame or no non-special after the filename token is found,
returns an error.
*/
static t_tkn_lst	*redirection(t_tkn_lst *token, t_cmd *cmd)
{
	if ((!token->next->content))
		return (error_msg(E_TOKEN, NULL, NULL), last_token(token));
	if (token->type == RD_IN)
		cmd->infile = token->next->content;
	else if (token->type == HERE)
	{
		cmd->delimiter = token->next->content;
		cmd->here_doc = 1;
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		cmd->outfile = token->next->content;
		if (token->type == APPEND)
			cmd->append = 1;
	}
	return (token->next->next);
}

void	parser(t_tkn_lst *token, t_data *data)
{
	int	proc_idx;

	proc_idx = 0;
	if (token->type == PIPE)
		error_msg(E_TOKEN, NULL, data);
	init_cmd(&data->cmds_tab[proc_idx]);
	while (token->type != END)
	{
		if (token->type == PIPE)
		{
			if (!token->next->content)
				error_msg(E_TOKEN, NULL, data);
			token = token->next;
			data->process_nb++;
			proc_idx++;
			init_cmd(&data->cmds_tab[proc_idx]);
		}
		if (token->type != END && token->content)
		{
			add_attribute(token, data, proc_idx);
			token = token->next;
		}
		else if (token->type != END && !token->content && token->type != PIPE)
			token = redirection(token, &data->cmds_tab[proc_idx]);
	}
}
