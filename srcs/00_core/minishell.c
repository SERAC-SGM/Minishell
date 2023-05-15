/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/15 16:38:29 by maaliber         ###   ########.fr       */
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

	(void)ac;
	(void)av;
	init_data(&data, env);
	enable_signal();
	while (1)
	{
		reset_data(&data);
		data.cmd_line = readline("42mini>");
		data.token_list = lexer(&data);
		print_lexer(data.token_list);
		//parser(data.token_list, &data);
		//print_cmds(&data);
		//exec_cmd_line(&data);
		clear_token_list(&data.token_list);
		//waitpid(-1, &data.status, 0);
		//if (data.exit == -1)
		//	break ;
	}
	ft_lstclear(&data.set);
	ft_lstclear(&data.env);
	data.status = WEXITSTATUS(data.status);
	return (data.status);
}
