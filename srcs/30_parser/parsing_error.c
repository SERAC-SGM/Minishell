/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:52:13 by matnam            #+#    #+#             */
/*   Updated: 2023/06/13 12:49:12 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			token_error_msg(token->next->type);
			g_sig.error_status = 2;
			return (1);
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
	init_cmd(&data->cmds_tab[proc_idx]);
	while (token->type != END)
	{
		token = parse_type(data, token, &proc_idx);
	}
	return (1);
}
