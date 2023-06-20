/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/20 16:04:34 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	display_prompt(t_data *data)
// {
// 	char	cwd[BUFFER_SIZE];
// 	char	*prompt;

// 	prompt = ft_strjoin(getcwd(cwd, BUFFER_SIZE), "$ ");
// 	data->cmd_line = readline(prompt);
// 	free(prompt);
// }

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
		//display_prompt(&data);
		// ft_printf("line %s\n", data.cmd_line);
		if (!data.cmd_line)
			break ;
		// ft_printf("line %s\n", data.cmd_line);
		if (*data.cmd_line)
		{
			add_history(data.cmd_line);
			lexer(&data);
			if (parser(&data))
				exec_cmd_line(&data);
			clear_token_list(&data.token_list);
		}
		// ft_printf("line %s\n", data.cmd_line);
	}
	clear_data(&data);
	write(1, "exit\n", 5);
	return (g_sig.error_status);
}
