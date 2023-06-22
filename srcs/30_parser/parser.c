/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/22 18:14:37 by maaliber         ###   ########.fr       */
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

/*
Check if the file is a TTY.
*/
static int	file_isatty(char *file, int read_write)
{
	int	fd;

	if (read_write == 0)
		fd = open(file, O_RDONLY);
	if (read_write == 1)
		fd = open(file, O_WRONLY);
	if (fd < 0)
		return (0);
	if (isatty(fd) == 1)
		return (close(fd), 1);
	else
		return (close(fd), 0);
}

/*
When encountering a redirection token (< << > >>), assings the correct
following filename to the command structure.
If no filemame or no non-special after the filename token is found,
returns 0.
*/
static void	redirection(t_tkn_lst *token, t_cmd *cmd)
{
	if (token->type == RD_IN)
	{
		if (!file_isatty(token->next->content, 0))
		{
			if (cmd->infile)
				free(cmd->infile);
			cmd->infile = ft_strdup(token->next->content);
		}
	}
	else if (token->type == HERE)
	{
		if (cmd->infile)
		{
			free(cmd->infile);
			cmd->infile = NULL;
		}
		cmd->delimiter = token->next->content;
		cmd->here_doc = 1;
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		if (!file_isatty(token->next->content, 1))
		{
			cmd->outfile = token->next->content;
			if (token->type == APPEND)
				cmd->append = 1;
		}
	}
}

t_tkn_lst	*parse_type(t_data *data, t_tkn_lst *token, int *proc_idx)
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
		redirection(token, &data->cmds_tab[*proc_idx]);
		token = token->next->next;
	}
	return (token);
}
