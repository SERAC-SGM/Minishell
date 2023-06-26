/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:13 by matnam            #+#    #+#             */
/*   Updated: 2023/06/26 16:13:15 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norminette_bypass_3000(t_tkn_lst *token, t_cmd *cmd)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	cmd->delimiter = token->next->content;
	cmd->here_doc = 1;
}

static void	token_error_msg(int token_type)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (token_type == PIPE)
		ft_putstr_fd("|'\n", 2);
	if (token_type == RD_IN)
		ft_putstr_fd("<'\n", 2);
	if (token_type == HERE)
		ft_putstr_fd("<<'\n", 2);
	if (token_type == RD_OUT)
		ft_putstr_fd(">'\n", 2);
	if (token_type == APPEND)
		ft_putstr_fd(">>'\n", 2);
	if (token_type == END)
		ft_putstr_fd("newline'\n", 2);
}

int	parsing_error(t_tkn_lst *token)
{
	while (token->type != END)
	{
		if (token->type != STD && token->next->type != STD)
		{
			if (token->type != PIPE || (token->type == PIPE
					&& (token->next->type == PIPE || token->next->type == END)))
			{
				token_error_msg(token->next->type);
				g_sig.error_status = 2;
				return (1);
			}
		}
		token = token->next;
	}
	return (0);
}

int	parser(t_data *data)
{
	t_tkn_lst	*token;
	int			proc_idx;

	if (!data->token_list || parsing_error(data->token_list))
		return (0);
	proc_idx = 0;
	token = data->token_list;
	init_cmd(&data->cmds_tab[0]);
	data->cmds_tab[0].process_index = 0;
	while (token->type != END)
		token = parse_type(data, token, &proc_idx);
	return (1);
}
