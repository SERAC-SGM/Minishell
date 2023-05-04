/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 17:27:21 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_files(t_tkn_lst *token, t_data *data)
{
	/* determine parse error behavior*/
	if (token->type == RD_IN)
		data->infile = token->next->content;
	else if (token->type == HERE)
		data->here_doc = 1;
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		data->outfile = token->next->content;
		data->outfile_mode = token->type;
	}
}

void	add_command(t_tkn_lst *token, t_data *data)
{
	data->command_list->cmd[data->command_list->cmd_count]
		= token->next->content;
	data->command_list->cmd_count++;
}

void	parser(t_tkn_lst *token, t_data *data)
{
	/*if (token->type == PIPE)
		Syntax error near unexpected token `|'*/
	while (token)
	{
		if (token->content)
			add_command(token, data);
		if (token->type == PIPE)
		{
			add_command(token, data);
			token = token->next;
		}
		if (!token->content)
		{	
			handle_files(token, data);
			token = token->next;
		}
		token = token->next;
	}
}


