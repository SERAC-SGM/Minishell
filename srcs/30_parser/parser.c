/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/13 23:57:10 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Returns the size of the command (name + optional arguments).
*/
char	**get_envpath(t_list *env)
{
	char	**path;
	int		i;

	i = 0;
	while (env)
	{
		if (!ft_strncmp("PATH", env[i], 4))
			break ;
		env = env->next;
	}
	path = ft_split(env[i] + 5, ':');
	return (path);
}

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

	data->cmds_tab[data->process_nb].attr
		= malloc(sizeof(char *) * (get_cmd_size(token) + 1));
	if (!data->cmds_tab)
		exit_error("malloc_error");
	data->cmds_tab[data->process_nb].attr[0] = token->content;
	token = token->next;
	i = 0;
	while (token->type != END && token->content)
	{
		data->cmds_tab[data->process_nb].attr[++i] = token->content;
		token = token->next;
	}
	data->cmds_tab[data->process_nb].arg_count = i;
	data->cmds_tab[data->process_nb].attr[++i] = NULL;
	data->cmds_tab[data->process_nb].process_index = data->process_nb;
	return (token);
}

void	parser(t_tkn_lst *token, t_data *data)
{
	if (token->type == PIPE)
		exit_error("syntax error near unexpected token `XXX'\n");
	data->env_path = get_envpath(data->env);
	init_cmd(&data->cmds_tab[data->process_nb]);
	while (token->type != END)
	{
		if (token->type == PIPE)
		{
			if (!token->next->content)
				exit_error("syntax error near unexpected token `XXX'\n");
			token = token->next;
			data->process_nb++;
			init_cmd(&data->cmds_tab[data->process_nb]);
		}
		if (token->type != END && token->content)
			token = add_command(token, data);
		else if (token->type != END && !token->content && token->type != PIPE)
			token = redirection(token, &data->cmds_tab[data->process_nb]);
	}
}
