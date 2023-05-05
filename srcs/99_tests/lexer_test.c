/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:35:39 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/05 14:28:22 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_lexer(t_tkn_lst	*lex)
{
	while (lex)
	{
		printf("type:[%d] | content: [%s]\n", lex->type, lex->content);
		lex = lex->next;
	}

}

void	init_env(t_data *data, char *env[])
{
	t_list	*env_list;
	t_list	*node;
	int		i;

	i = 0;
	if (!env)
		return ;
	env_list = NULL;
	while (env[i])
	{
		node = ft_lstnew(ft_strdup(env[i]));
		if (!node)
		{
			ft_lstclear(&env_list);
			break ;
		}	
		ft_lstadd_back(&env_list, node);
		i++;
	}
	data->env = env_list;
	return ;
}

int	main(int ac, char *av[], char *env[])
{
	t_data		data;
	t_tkn_lst	*lex;
	(void)ac;
	(void)av;
	(void)env;

	ft_bzero(&data, sizeof(t_data));
	init_env(&data, env);
	data.cmd_line = get_next_line(0);
	lex = lexer(&data);
	print_lexer(lex);
	free(data.cmd_line);
}