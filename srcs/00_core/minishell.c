/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 18:33:35 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_data	data;
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	init_data(&data, env);
	enable_signal();
	while (i++ < 20)
	{
		reset_data(&data);
		if (isatty(STDIN_FILENO))
		{
			data.cmd_line = readline("42mini>");
			add_history(data.cmd_line);
		}
		else
			data.cmd_line = get_next_line(STDIN_FILENO);
		data.token_list = lexer(&data);
		//print_lexer(data.token_list);
		parser(data.token_list, &data);
		//print_cmds(&data);
		exec_cmd_line(&data);
		clear_token_list(&data.token_list);
		if (g_sig.exit == 1)
			break ;
	}
	rl_clear_history();
	clear_data(&data);
	data.status = WEXITSTATUS(data.status);
	return (data.status);
}
