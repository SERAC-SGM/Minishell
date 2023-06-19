/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:06 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/19 14:45:42 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*heredoc_name(int proc_nb)
{
	char	*name;
	char	*nb;

	nb = ft_itoa(proc_nb);
	name = ft_strjoin(".here_doc", nb);
	free(nb);
	return (name);
}

static int	wait_heredoc(int fd_hdoc, t_cmd *cmd, char *line, t_data *data)
{
	int	status;

	disable_signal();
	status = 0;
	ret = 1;
	if (g_sig.pid == 0)
	{
		close(fd_hdoc);
		if (!line)
			exit_heredoc(cmd, data);
		free(line);
		clear_exit(data);
	}
	while (waitpid(g_sig.pid, &status, 0) != -1)
		;
	enable_signal();
	if (WIFSIGNALED(status))
		return (0);
	return (1);
}

int	input_heredoc(t_cmd *cmd, t_data *data)
{
	char		*line;
	int			fd_hdoc;
	int			ret;

	cmd->infile = heredoc_name(cmd->process_index);
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
	ret = wait_heredoc(fd_hdoc, cmd, line, data);
	return (ret);
}
