/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:06 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/28 12:48:32 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_heredoc(t_cmd *cmd, char *line, t_data *data)
{
	int		i;

	i = -1;
	while (++i < data->process_nb)
		close_files(&data->cmds_tab[i]);
	free_infile(data, cmd->process_index);
	if (line)
		free(line);
	else if (g_sig.error_status != 130)
	{
		ft_putstr_fd("\n", 2);
		ft_putstr_fd(MSG_HEREDOC, 2);
		ft_putstr_fd(cmd->delimiter, 2);
		ft_putstr_fd("\')\n", 2);
	}
	clear_data(data);
	exit(g_sig.error_status);
}

static int	wait_heredoc(t_cmd *cmd, char *line, t_data *data)
{
	int	status;

	close(cmd->fd_hdoc);
	status = 0;
	if (g_sig.pid == 0)
		exit_heredoc(cmd, line, data);
	disable_signal();
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		g_sig.error_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_sig.error_status = WTERMSIG(status) + 128;
	if (g_sig.error_status == 130)
		return (0);
	enable_signal();
	return (1);
}

int	input_heredoc(t_cmd *cmd, t_data *data)
{
	char		*line;

	cmd->fd_hdoc = open(cmd->infile_hdoc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
			write(cmd->fd_hdoc, line, ft_strlen(line));
			free(line);
		}
	}
	if (!wait_heredoc(cmd, line, data))
		return (write(1, "\n", 1), 0);
	return (1);
}
