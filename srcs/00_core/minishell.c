/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 12:48:47 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_cmd(t_data *data)
{
	
}

void	exec_cmd_line(t_data *data)
{
	t_tkn_lst	*lex;

	while (get_next_line(0, &line) > 0)
	{
		data->cmd_line = get_next_line(0);
		data->cmd_line = free_strtrim(data->cmd_line, "\v\t ");
		if (!data->cmd_line)
			exit_error(E_MEM, data);
		lex = lexer(data);
		parser(data, lex);
		expander(data);
		executor(data);
	}
}

void	init_env(t_data *data, char *env[])
{
	t_list	*node;
	int		i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
			ft_lstclear(&data->env);
		ft_lstadd_back(&data->env, node);
	}
	return ;
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;
	
	(void)ac;
	(void)av;
	ft_bzero(&data, sizeof(t_data));
	init_env(&data, env);
	while (1)
	{
		reset_cmd(&data);
		exec_cmd_line(&data);
		waitpid(-1, &data.status, NULL);
		if (data.exit = -1)
			break ;
	}
	data.status = WEXITSTATUS(data.status);
	return (data.status);
}