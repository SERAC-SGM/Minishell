/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_managemer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/13 23:57:49 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn_lst	*redirection(t_tkn_lst *token, t_cmd *cmd)
{
	if ((!token->next->content))
		exit_error("syntax error near unexpected token `XXX'\n");
	if (token->type == RD_IN)
		cmd->infile = token->next->content;
	else if (token->type == HERE)
		cmd->delimiter = token->next->content;
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		cmd->outfile = token->next->content;
		if (token->type == APPEND)
			cmd->append = 1;
	}
	return (token->next->next);
}

void	write_heredoc(t_cmd *cmd)
{
	char	*line;

	cmd->fd_in = open(".here_doc", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (cmd->fd_in == -1)
		msg_error();
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

void	check_open_error(int fd, t_data *data)
{
	(void)data;
	if (fd == -1)
		msg_error("Open");
}

void	open_files(t_cmd *cmd, t_data *data)
{
	if (cmd->infile)
	{
		cmd->fd_in = open(cmd->infile, O_RDONLY, 644);
		check_open_error(cmd->fd_in, data);
	}
	else if (cmd->here_doc)
	{
		write_heredoc(cmd);
		cmd->fd_in = open(".here_doc", O_RDONLY | O_CREAT | O_EXCL, 644);
	}
	if (cmd->outfile)
	{
		if (!cmd->append)
		cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 644);
		else
			cmd->fd_out = open(cmd->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 644);
		check_open_error(cmd->fd_out, data);
	}
}

void	close_files(t_cmd *cmd)
{
	if (cmd->infile || cmd->here_doc)
	{
		close(cmd->fd_in);
		cmd->infile = NULL;
		if (cmd->here_doc)
			unlink(".here_doc");
	}
	if (cmd->outfile)
	{
		close(cmd->fd_out);
		cmd->outfile = NULL;
	}
}
