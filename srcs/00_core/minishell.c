/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:58:49 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/23 12:52:41 by maaliber         ###   ########.fr       */
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

// void    print_cmd(t_cmd *cmd)
// {
//     if (!cmd)
//         return (printf("Error Parsing\n"), (void)0);
//     printf("\n-----------\nIndex:[%d]\n-----------\n", cmd->process_index);
//     printf("Args_count:%d\n", cmd->arg_count);
//     print_tab(cmd->attr);
//     printf("Infile:%s\n", cmd->infile);
//     printf("Here_doc:%d\n", cmd->here_doc);
//     printf("Limiter:%s\n", cmd->delimiter);
//     printf("Outfile:%s\n", cmd->outfile);
//     printf("Append:%d\n", cmd->append);
// }

// void    print_cmds(t_data *data)
// {
//     int    i;

//     i = 0;
//     while (i < data->process_nb)
//         print_cmd(&data->cmds_tab[i++]);
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
