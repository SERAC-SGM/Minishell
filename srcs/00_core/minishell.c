/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/01 13:11:22 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char *av[], char *env[])
{
	t_data	data;

	(void)ac;
	(void)av;
	enable_signal();
	init_data(&data, env);
	while (!g_sig.exit)
	{
		reset_data(&data);
		data.cmd_line = readline("minishell$ ");
		if (!data.cmd_line)
			break ;
		if (*data.cmd_line)
		{
			add_history(data.cmd_line);
			data.token_list = lexer(&data);
			if (parser(data.token_list, &data))
				exec_cmd_line(&data);
			clear_token_list(&data.token_list);
		}
	}
	clear_data(&data);
	write(1, "exit\n", 5);
	return (g_sig.error_status);
}
