/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:06 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/24 22:48:13 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exit_heredoc(int fd_hdoc, char *lim, char *line, t_data *data)
{
	int	status;

	status = 0;
	if (g_sig.pid == 0)
	{
		close(fd_hdoc);
		if (!line)
			exit_error(E_HEREDOC, lim, data);
		free(line);
		clear_exit(data);
	}
	while (waitpid(g_sig.pid, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		return (0);
	return (1);
}

int	input_heredoc(t_cmd *cmd, t_data *data)
{
	char		*line;
	int			fd_hdoc;
	int			ret;

	cmd->infile = ft_strjoin(".here_doc", ft_itoa(cmd->process_index));
	fd_hdoc = open(cmd->infile, O_WRONLY | O_CREAT | O_EXCL, 0644);
	line = NULL;
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		exit_error(E_FORK, 0, data);
	if (g_sig.pid == 0)
	{
		while (1)
		{
			write(1, ">", 1);
			line = get_next_line(0);
			if (!line || ft_strcmp(line, cmd->delimiter) == '\n')
				break ;
			write(fd_hdoc, line, ft_strlen(line));
			free(line);
		}
	}
	ret = exit_heredoc(fd_hdoc, cmd->delimiter, line, data);
	return (ret);
}
