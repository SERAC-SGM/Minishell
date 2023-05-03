/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 11:50:40 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd_line(t_data *data)
{
	char	**lex;
	
	data->cmd_line = readline(READLINE_MSG);
	data->cmd_line = free_strtrim(data->cmd_line, "\v\t ");
	if (!data->cmd_line)
		exit_error(E_MEM, data);
	lex = lexer(data->cmd_line);
	parser(&data, lex);
	expander(&data);
	executor(&data);
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