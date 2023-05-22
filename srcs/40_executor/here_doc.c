/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:06 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/22 17:12:10 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_heredoc(t_cmd *cmd) // A CHANGER
{
	char	*line;

	cmd->infile = ft_strjoin(".here_doc_", ft_itoa(cmd->process_index));
	cmd->fd_in = open(cmd->infile, O_WRONLY | O_CREAT | O_EXCL, 0644);
	check_open_error(cmd->fd_in, cmd);
	while (1)
	{
		line = readline("$>");
		if (!line)
			return (0);
		if (ft_strncmp(line, cmd->delimiter, ft_strlen(cmd->delimiter) + 1) == '\n')
			break ;
		write(cmd->fd_in, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(cmd->fd_in);
	return (1);
}
