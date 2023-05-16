/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:51:50 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 15:35:32 by maaliber         ###   ########.fr       */
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
	cmd->arg_count = 0;
	cmd->attr = NULL;
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
	int	i;

	i = 0;
	ft_bzero(data, sizeof(t_data));
	while (i < OPEN_MAX)
		data->fd[i++] = -1;
	data->process_nb = 1;
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
	while (data->cmds_tab[i].process_index >= 0)
	{
		free(data->cmds_tab[i].attr);
		init_cmd(&data->cmds_tab[i]);
		i++;
	}
	i = 0;
	while (i < OPEN_MAX)
		data->fd[i++] = -1;
}
