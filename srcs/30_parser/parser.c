/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/02 12:19:57 by lletourn         ###   ########.fr       */
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
Creates the outfile and closes it. If the outfile is a TTY, ignores it.
*/
static void	create_file(t_cmd *cmd)
{
	open_files(cmd);
	if (isatty(cmd->fd_out) == 1)
	{
		close(cmd->fd_out);
		cmd->outfile = NULL;
		cmd->fd_out = 0;
		cmd->append = 0;
		return ;
	}
	close(cmd->fd_out);
}

/*
When encountering a redirection token (< << > >>), assings the correct
following filename to the command structure.
If no filemame or no non-special after the filename token is found,
returns 0.
*/
static int	redirection(t_tkn_lst *token, t_cmd *cmd)
{
	if ((!token->next->content))
		return (error_msg(E_TOKEN, NULL, NULL), 0);
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
		create_file(cmd);
	}
	return (1);
}

int	parser(t_tkn_lst *token, t_data *data)
{
	int	proc_idx;

	proc_idx = 0;
	if (token->type == PIPE)
		return (error_msg(E_TOKEN, "|", data), 0);
	init_cmd(&data->cmds_tab[proc_idx]);
	while (token->type != END)
	{
		if (token->type == PIPE)
		{
			if (!token->next->content)
				return (error_msg(E_TOKEN, "|", data), 0);
			token = token->next;
			data->process_nb++;
			init_cmd(&data->cmds_tab[++proc_idx]);
		}
		if (token->type == STD)
		{
			if (token->content)
				add_attribute(token, data, proc_idx);
			token = token->next;
		}
		if (token->type != END && !token->content && token->type != PIPE)
		{	
			if (!redirection(token, &data->cmds_tab[proc_idx]))
				return (error_msg(E_TOKEN, "|", data), 0);
			token = token->next->next;
		}
	}
	return (1);
}
