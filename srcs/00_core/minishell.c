/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 16:56:53 by maaliber         ###   ########.fr       */
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
		lex = lexer(data->cmd_line);
		parser(data, lex);
		expander(data);
		executor(data);
	}
}


int	main(int ac, char *av[], char *env[])
{
	t_data	data;
	
	(void)ac;
	(void)av;
	data.env = init_env(env);
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