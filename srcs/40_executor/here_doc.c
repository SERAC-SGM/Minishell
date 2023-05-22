/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:06 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/22 16:44:39 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	input_heredoc(t_cmd *cmd) // A CHANGER
{
	char	*line;

	line = "";
	ft_printf("heredoc> ", 1);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strlen(cmd->delimiter) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, cmd->delimiter, ft_strlen(cmd->delimiter)))
		{
			close(cmd->fd_in);
			close(0);
		}
		else
		{
			ft_printf("heredoc> ", 1);
			write(cmd->fd_in, line, ft_strlen(line));
		}
		free(line);
	}
}

void	write_heredoc(t_cmd *cmd)
{
	char	*str_process_index;

	str_process_index = ft_itoa(cmd->process_index);
	cmd->infile = ft_strjoin(".here_doc_", str_process_index);
	free(str_process_index);
	cmd->fd_in = open(cmd->infile, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (cmd->fd_in == -1)
		error_msg(E_PERM, cmd->infile, NULL);
	input_heredoc(cmd);
}
