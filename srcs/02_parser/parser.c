/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 13:02:35 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the size of the command (name + optional arguments).
*/
int	get_cmd_size(t_tkn_lst *token, t_data *data)
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
t_tkn_lst	*add_command(t_tkn_lst *token, t_data *data)
{
	int	i;

	data->command_list[data->cmd_count].cmd
		= malloc(sizeof(char *) * (get_cmd_size(token, data) + 1));
	// if (!data->command_list)
	// 	exit_error("malloc_error");
	data->command_list[data->cmd_count].cmd[0] = token->content;
	token = token->next;
	i = 0;
	while (token && token->content)
	{
		data->command_list[data->cmd_count].cmd[++i] = token->content;
		token = token->next;
	}
	data->command_list[data->cmd_count].arg_count = i;
	data->command_list[data->cmd_count].cmd[++i] = NULL;
	data->command_list[data->cmd_count].process_index = data->cmd_count;
	return (token->next);
}

t_tkn_lst	*process_parser(t_tkn_lst *token, t_data *data)
{
	while (token)
	{
		if (token->type == PIPE)
		{
			// if (!token->next->content)
				// exit_error("syntax error near unexpected token `XXX'\n");
			token = token->next;
			data->cmd_count++;
		}
		if (token && token->content)
			token = add_command(token, data);
		else if (token && !token->content && token->type != PIPE)
			token = handle_files(token, data);
	}
	return (token->next);
}

void	check_error()
{
	return ;
}

void	parser(t_tkn_lst *token, t_data *data)
{
	//if (token->type == PIPE)
	//	printf("syntax error near unexpected token `XXX'\n");
	while (token)
	{
		if (token && token->content)
			token = add_command(token, data);
		else if (token && token->type == PIPE)
			token = add_command(token->next, data);
		else if (token && !token->content)
			token = handle_files(token, data);
		else if (token)
			token = token->next;
	}
}
