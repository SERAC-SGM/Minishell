/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:39:49 by matnam            #+#    #+#             */
/*   Updated: 2023/06/06 14:16:17 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ambiguous_redir_error_msg(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]) && !is_special(&str[i]))
		i++;
	ft_putstr_fd("minishell: ", 2);
	write(2, str, i);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	error_ambiguous(t_tkn_lst *token, char *cmd_line, t_data *data)
{
	char	*file_name;
	char	*cmd_l;

	if (token->type == RD_IN || token->type == RD_OUT
		|| token->type == APPEND)
	{
		while (*cmd_line && ft_isspace(*cmd_line))
			cmd_line++;
		if (*cmd_line == '$')
		{
			cmd_l = cmd_line;
			file_name = standard_mode(&cmd_l, data->env);
			if (!*file_name)
			{
				ambiguous_redir_error_msg(cmd_line);
				g_sig.error_status = 1;
				return (free(file_name), 1);
			}
			free(file_name);
		}
	}
	return (0);
}