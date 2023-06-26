/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 14:44:06 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/26 14:22:30 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_infile(t_data *data, int proc_idx)
{
	int	i;

	i = -1;
	while (++i <= proc_idx)
	{
		if (data->cmds_tab[i].infile)
		{
			if (data->cmds_tab[i].fd_in > 2)
				close(data->cmds_tab[i].fd_in);
			free(data->cmds_tab[i].infile);
		}
		if (data->cmds_tab[i].infile_hdoc)
			free(data->cmds_tab[i].infile_hdoc);
	}
}

static char	*heredoc_name(int proc_nb)
{
	char	*name;
	char	*nb;

	nb = ft_itoa(proc_nb);
	name = ft_strjoin(".here_doc", nb);
	free(nb);
	return (name);
}

static void	exit_heredoc(t_cmd *cmd, char *line, t_data *data)
{
	char	*err_msg;
	int		i;

	i = -1;
	while (++i < data->process_nb)
		close_files(&data->cmds_tab[i]);
	free_infile(data, cmd->process_index);
	if (!line)
	{
		err_msg = ft_strjoin(MSG_HEREDOC, cmd->delimiter);
		err_msg = ft_strjoin_dup1(err_msg, "\')\n");
		ft_putstr_fd(err_msg, 2);
		free(err_msg);
		clear_data(data);
		exit(1);
	}
	free(line);
	clear_data(data);
	exit(0);
}

static int	wait_heredoc(t_cmd *cmd, char *line, t_data *data)
{
	int	status;

	disable_signal();
	close(cmd->fd_hdoc);
	status = 0;
	if (g_sig.pid == 0)
		exit_heredoc(cmd, line, data);
	while (waitpid(-1, &status, 0) != -1)
		;
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		status = WTERMSIG(status) + 128;
	if (status == 130)
		return (0);
	enable_signal();
	return (1);
}

int	input_heredoc(t_cmd *cmd, t_data *data)
{
	char		*line;

	cmd->infile_hdoc = heredoc_name(cmd->process_index);
	cmd->fd_hdoc = open(cmd->infile_hdoc, O_WRONLY | O_CREAT | O_EXCL, 0644);
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
