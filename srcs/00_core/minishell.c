/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/22 15:14:27 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		data.cmd_line = readline("\033[1;34m42\033[1;36mniquelabac\033[0m▸");
		if (!data.cmd_line)
			break ;
		add_history(data.cmd_line);
		data.token_list = lexer(&data);
		parser(data.token_list, &data);
		exec_cmd_line(&data);
		clear_token_list(&data.token_list);
	}
	clear_data(&data);
	write(1, "exit\n", 5);
	return (0);
}
