/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:51:50 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/05 10:48:21 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_data *data, char *env[])
{
	t_list	*node;
	char	cwd[BUFFER_SIZE];
	int		i;

	i = 0;
	if (!env[0])
	{
		getcwd(cwd, BUFFER_SIZE);
		set_env_var("PWD", cwd, data, 0);
		set_env_var("_", "./minishell", data, 0);
		return ;
	}
	while (env[i])
	{
		node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
		{
			ft_lstclear(&data->env);
			break ;
		}	
		ft_lstadd_back(&data->env, node);
		i++;
	}
}

void	init_cmd(t_cmd *cmd)
{
	cmd->process_index = 0;
	cmd->arg_count = 0;
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->fd_in = STDIN_FILENO;
	cmd->here_doc = 0;
	cmd->delimiter = NULL;
	cmd->outfile = NULL;
	cmd->fd_out = STDOUT_FILENO;
	cmd->append = 0;
}

void	init_data(t_data *data, char *env[])
{
	int	i;

	i = 0;
	ft_bzero(data, sizeof(t_data));
	while (i < OPEN_MAX / 2)
	{
		data->fd[i][0] = -1;
		data->fd[i][1] = -1;
		++i;
	}
	data->process_nb = 1;
	init_env(data, env);
	return ;
}

/*
Returns the size of the command (name + optional arguments).
*/
static char	**get_envpath(t_list *env)
{
	char	**path;

	while (env)
	{
		if (!ft_strncmp("PATH", env->line, 4))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	path = ft_split(env->line + 5, ':');
	return (path);
}

void	reset_data(t_data *data)
{
	int	i;

	i = 0;
	free(data->cmd_line);
	data->cmd_line = NULL;
	free_tab(data->env_path);
	data->env_path = get_envpath(data->env);
	data->process_nb = 1;
	clear_token_list(&data->token_list);
	while (data->cmds_tab[i].args)
	{
		if (data->cmds_tab[i].args[0])
			free(data->cmds_tab[i].args[0]);
		free(data->cmds_tab[i].args);
		data->cmds_tab[i].args = NULL;
		init_cmd(&data->cmds_tab[i]);
		i++;
	}
	i = 0;
	while (i < OPEN_MAX / 2)
	{
		data->fd[i][0] = -1;
		data->fd[i][1] = -1;
		++i;
	}
}
