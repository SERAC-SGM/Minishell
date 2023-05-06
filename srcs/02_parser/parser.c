/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 12:14:22 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Adds a new command in the data structure. The first token is used as the name of
the command, and all following non-special tokens as optional arguments.
Returns the next special token.
*/
t_tkn_lst	*add_command(t_tkn_lst *token, t_data *data)
{
	int	index;

	index = 0;
	data->command_list[data->cmd_count].cmd = malloc(sizeof(char *) * 100);//get malloc size
	data->command_list[data->cmd_count].cmd[index++] = token->content;
	token = token->next;
	while (token && token->content)
	{
		data->command_list[data->cmd_count].cmd[index++] = token->content;
		token = token->next;
	}
	data->command_list[data->cmd_count].arg_count = index;
	data->command_list[data->cmd_count].cmd[index] = NULL;
	data->command_list[data->cmd_count].process_index = data->cmd_count;
	data->cmd_count++;
	return (token);
}

t_tkn_lst	*process_parser(t_tkn_lst *token, t_data *data)
{
	while (token && token->type != PIPE)
	{
		if (token && token->content)
			token = add_command(token, data);
		else if (token && !token->content && token->type != PIPE)
			token = handle_files(token, data);
	}
	return (token);
}

void	pipe_parser(t_tkn_lst *token, t_data *data)
{
	return ;
}

void	parser(t_tkn_lst *token, t_data *data)
{
	if (token->type == PIPE)
		printf("syntax error near unexpected token `XXX'\n");
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
