/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 19:53:14 by matnam           ###   ########.fr       */
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
		data.cmd_line = readline(prompt());
		exec_cmd_line(&data);
		waitpid(-1, &data.status, 0);
		if (data.exit == -1)
			break ;
	}
	ft_lstclear(&data.env);
	data.status = WEXITSTATUS(data.status);
	return (data.status);
}
