/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/10 12:39:09 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tkn_lst	*handle_files(t_tkn_lst *token, t_cmd *cmd)
{
	if ((!token->next->content))
		exit_error("syntax error near unexpected token `XXX'\n");
	if (token->type == RD_IN)
	{
		cmd->infile = token->next->content;
		//data->fd_infile = open(data->infile, O_RDONLY, 644);//error open
	}
	else if (token->type == HERE)
	{
		//write_tmp(data);
		//data->fd_infile = open(".here_doc", O_RDONLY, 644);
		cmd->delimiter = token->next->content;
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		cmd->outfile = token->next->content;
		//if (token->type == RD_OUT)	q 
			//data->fd_outfile = open(data->outfile,
			//		O_WRONLY | O_TRUNC | O_CREAT, 644);
		//else
			//data->fd_outfile = open(data->outfile,
			//		O_WRONLY | O_APPEND | O_CREAT, 644);
	}
	return (token->next->next);
}

void	write_heredoc(t_cmd *cmd)
{
	char	*line;

	cmd->fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (cmd->fd_infile == -1)
		exit_error();
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
			close(cmd->fd_infile);
			close(0);
		}
		else
		{
			ft_printf("heredoc> ", 1);
			write(cmd->fd_infile, line, ft_strlen(line));
		}
		free(line);
	}
}

void	open_files(t_cmd *cmd)
{
	
}
