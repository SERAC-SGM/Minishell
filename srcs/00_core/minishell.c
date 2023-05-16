/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 15:46:21 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	exec_cmd_line(t_data *data)
{
	t_tkn_lst	*lex;

	lex = lexer(data->cmd_line);
	print_lexer(lex);
	parser(data, lex);
	clear_token_list(&lex);
	free(data->cmd_line);
}*/

int	main(int ac, char *av[], char *env[])
{
	t_data	data;
	int	i;

	(void)ac;
	(void)av;
	i = 0;
	init_data(&data, env);
	enable_signal();
	while (i++ < 1)
	{
		reset_data(&data);
		if (isatty(STDIN_FILENO))
			data.cmd_line = readline("42mini>");
		else
			data.cmd_line = get_next_line(STDIN_FILENO);
		data.token_list = lexer(&data);
		print_lexer(data.token_list);
		parser(data.token_list, &data);
		print_cmds(&data);
		//exec_cmd_line(&data);
		clear_token_list(&data.token_list);
		//waitpid(-1, &data.status, 0);
		if (g_sig.exit == 1)
			break ;
	}
	clear_data(&data);
	data.status = WEXITSTATUS(data.status);
	return (data.status);
}
