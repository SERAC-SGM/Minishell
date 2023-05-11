/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:51:50 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 14:53:48 by maaliber         ###   ########.fr       */
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
Initializes a data structure.
*/
void	init_data(t_data *data, char *env[])
{
	ft_bzero(data, sizeof(t_data));
	init_env(data, env);
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
	cmd->fd_infile = 0;
	cmd->outfile = NULL;
	cmd->fd_outfile = 1;
	cmd->here_doc = 0;
	cmd->delimiter = NULL;
}
