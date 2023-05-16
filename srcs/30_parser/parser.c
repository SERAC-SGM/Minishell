/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 13:39:10 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the size of the command (name + optional arguments).
*/
char	**get_envpath(t_list *env)
{
	char	**path;

	while (env)
	{
		if (!ft_strncmp("PATH", env->line, 4))
			break ;
		env = env->next;
	}
	path = ft_split(env->line + 5, ':');
	return (path);
}

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
static t_tkn_lst	*set_command(t_tkn_lst *token, t_data *data, int proc_idx)
{
	int	i;
	int	size;

	size = get_cmd_size(token);
	if (!data->cmds_tab[proc_idx].attr)
	{
		data->cmds_tab[proc_idx].attr = ft_calloc(size + 1, sizeof(char *));
		if (!data->cmds_tab[proc_idx].attr)
			return (error_msg(E_MEM, NULL, data), NULL);
	}
	i = tab_size(data->cmds_tab[proc_idx].attr);
	data->cmds_tab[proc_idx].attr[i] = token->content;
	token = token->next;
	while (token->type != END && token->content)
	{
		data->cmds_tab[proc_idx].attr[++i] = token->content;
		token = token->next;
	}
	data->cmds_tab[proc_idx].arg_count = i;
	data->cmds_tab[proc_idx].attr[++i] = NULL;
	data->cmds_tab[proc_idx].process_index = proc_idx;
	return (token);
}

void	parser(t_tkn_lst *token, t_data *data)
{
	int	proc_idx;

	proc_idx = 0;
	if (token->type == PIPE)
		error_msg(E_TOKEN, NULL, data);
	data->env_path = get_envpath(data->env);
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
			token = set_command(token, data, proc_idx);
		else if (token->type != END && !token->content && token->type != PIPE)
			token = redirection(token, &data->cmds_tab[proc_idx]);
	}
}
