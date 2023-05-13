/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:51:50 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/13 18:56:08 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Initializes a environment list.
*/
void	init_env(t_data *data, char *env[])
{
	t_list	*env_list;
	t_list	*node;
	int		i;

	i = 0;
	if (!env)
		return ;
	env_list = NULL;
	while (env[i])
	{
		node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
		{
			ft_lstclear(&env_list);
			break ;
		}	
		ft_lstadd_back(&env_list, node);
		i++;
	}
	data->env = env_list;
	return ;
}

/*
Initializes a command structure.
*/
void	init_cmd(t_cmd *cmd)
{
	cmd->process_index = 0;
	cmd->pid = 0;
	cmd->arg_count = 0;
	cmd->cmd = NULL;
	cmd->infile = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->here_doc = 0;
	cmd->outfile = NULL;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
	cmd->delimiter = NULL;
}

/*
Initializes a data structure.
*/
void	init_data(t_data *data, char *env[])
{
	ft_bzero(data, sizeof(t_data));
	init_env(data, env);
	return ;
}

/*
Reset data structure to receive new command input :
Free all allocated memory related to command input
Keep environment variables.
*/
void	reset_data(t_data *data)
{
	int	i;

	i = 0;
	free(data->cmd_line);
	data->cmd_line = NULL;
	clear_token_list(&data->token_list);
	while (data->cmd_list[i].cmd)
	{
		free(data->cmd_list[i].cmd);
		init_cmd(data->cmd_list[i]);
		i++;
	}
}
