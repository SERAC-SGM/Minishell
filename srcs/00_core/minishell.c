/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/31 12:12:41 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Waits for each process to finish.
*/
static void	wait_process(void)
{
	int	status;

	status = 0;
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		g_sig.error_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig.error_status = WTERMSIG(status) + 128;
}

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	(void)ac;
	(void)av;
	init_data(&data, env);
	enable_signal();
	while (!g_sig.exit)
	{
		reset_data(&data);
		data.cmd_line = readline("minishell$ ");
		if (!data.cmd_line)
			break ;
		add_history(data.cmd_line);
		data.token_list = lexer(&data);
		parser(data.token_list, &data);
		exec_cmd_line(&data);
		wait_process();
		clear_token_list(&data.token_list);
	}
	clear_data(&data);
	write(1, "exit\n", 5);
	return (g_sig.error_status);
}
