/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 11:14:45 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/27 11:19:16 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	norminette_bypass_3000(t_tkn_lst *token, t_cmd *cmd)
{
	if (cmd->infile)
	{
		free(cmd->infile);
		cmd->infile = NULL;
	}
	cmd->delimiter = token->next->content;
	cmd->here_doc = 1;
}

/*
Check if the file is a TTY.
*/
static int	file_isatty(char *file, int read_write)
{
	int	fd;

	if (!file)
		return (0);
	if (read_write == 0)
		fd = open(file, O_RDONLY);
	if (read_write == 1)
		fd = open(file, O_WRONLY | O_CREAT, 0655);
	if (fd < 0)
		return (0);
	if (isatty(fd) == 1)
		return (close(fd), 1);
	else
		return (close(fd), 0);
}

void	redirection(t_tkn_lst *token, t_cmd *cmd)
{
	if (token->type == RD_IN)
	{
		if (!file_isatty(token->next->content, 0))
		{
			if (cmd->infile)
				free(cmd->infile);
			cmd->infile = ft_strdup(token->next->content);
		}
	}
	else if (token->type == HERE)
		norminette_bypass_3000(token, cmd);
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		if (!file_isatty(token->next->content, 1))
		{
			cmd->outfile = token->next->content;
			if (token->type == APPEND)
				cmd->append = 1;
		}
	}
}
