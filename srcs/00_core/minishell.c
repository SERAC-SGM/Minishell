/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/28 10:24:44 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	display_prompt(t_data *data)
{
	char	*prompt;
	char	*var;

	var = get_var_value("PWD", data->env);
	if (!var)
		prompt = ft_strdup("$ ");
	else
		prompt = ft_strjoin(get_var_value("PWD", data->env), "$ ");
	data->cmd_line = readline(prompt);
	free(prompt);
}

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
		display_prompt(&data);
		if (!data.cmd_line)
			break ;
		if (*data.cmd_line)
		{
			add_history(data.cmd_line);
			lexer(&data);
			if (parser(&data))
				exec_cmd_line(&data);
			clear_token_list(&data.token_list);
		}
	}
	clear_data(&data);
	write(1, "exit\n", 5);
	return (g_sig.error_status);
}
