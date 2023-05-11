/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 14:54:49 by maaliber         ###   ########.fr       */
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
	while (token && token->content)
	{
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
static t_tkn_lst	*add_command(t_tkn_lst *token, t_data *data)
{
	int	i;

	data->command_list[data->cmd_count].cmd
		= malloc(sizeof(char *) * (get_cmd_size(token) + 1));
	if (!data->command_list)
		exit_error("malloc_error");
	data->command_list[data->cmd_count].cmd[0] = token->content;
	token = token->next;
	i = 0;
	while (token->type != END && token->content)
	{
		data->command_list[data->cmd_count].cmd[++i] = token->content;
		token = token->next;
	}
	data->command_list[data->cmd_count].arg_count = i;
	data->command_list[data->cmd_count].cmd[++i] = NULL;
	data->command_list[data->cmd_count].process_index = data->cmd_count;
	return (token);
}

void	parser(t_tkn_lst *token, t_data *data)
{
	if (token->type == PIPE)
		exit_error("syntax error near unexpected token `XXX'\n");
	init_cmd(&data->command_list[data->cmd_count]);
	while (token->type != END)
	{
		if (token->type == PIPE)
		{
			if (!token->next->content)
				exit_error("syntax error near unexpected token `XXX'\n");
			token = token->next;
			data->cmd_count++;
			init_cmd(&data->command_list[data->cmd_count]);
		}
		if (token->type != END && token->content)
			token = add_command(token, data);
		else if (token->type != END && !token->content && token->type != PIPE)
			token = handle_files(token, &data->command_list[data->cmd_count]);
	}
}
