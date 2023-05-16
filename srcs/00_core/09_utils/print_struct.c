/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:56:50 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 13:39:19 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_tkn_lst *lex)
{
	printf("\n-----------\nTokens\n-----------\n");
	while (lex)
	{
		printf("type:[%d] | content: [%s]\n", lex->type, lex->content);
		lex = lex->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	printf("Name:%s\n", tab[0]);
	i = 1;
	printf("Args:\n");
	while (tab[i])
		printf("     %s\n", tab[i++]);
}

void	print_cmd(t_cmd *cmd)
{
	printf("\n-----------\nIndex:[%d]\n-----------\n", cmd->process_index);
	printf("Args_count:%d\n", cmd->arg_count);
	print_tab(cmd->attr);
	printf("Infile:%s\n", cmd->infile);
	printf("Here_doc:%d\n", cmd->here_doc);
	printf("Limiter:%s\n", cmd->delimiter);
	printf("Outfile:%s\n", cmd->outfile);
	printf("Append:%d\n", cmd->append);
}

void	print_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->process_nb)
		print_cmd(&data->cmds_tab[i++]);
}

void	print_env(t_list *env)
{
	while (env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}
