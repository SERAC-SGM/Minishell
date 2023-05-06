/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/06 12:13:42 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_tmp(t_data *data)
{
	char	*line;

	data->fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (data->fd_infile == -1)
		ft_exit(data, NULL, 0, 0);
	line = "";
	ft_printf("heredoc> ", 1);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strlen(data->delimiter) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, data->delimiter, ft_strlen(data->delimiter)))
		{
			close(data->fd_infile);
			close(0);
		}
		else
		{
			ft_printf("heredoc> ", 1);
			write(data->fd_infile, line, ft_strlen(line));
		}
		free(line);
	}
}

void	close_previous_file(t_data *data, t_tkn_lst *token)
{
	if (token->type == RD_IN || token->type == HERE)
	{
		if (data->fd_infile != 0)
			close(data->fd_infile);
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		if (data->fd_outfile != 1)
			close(data->fd_outfile);
	}
}

t_tkn_lst	*handle_files(t_tkn_lst *token, t_data *data)
{
	if ((!token->next->content))
		printf("syntax error near unexpected token `XXX'\n");
	close_previous_file(data, token);
	if (token->type == RD_IN)
	{
		data->infile = token->next->content;
		data->fd_infile = open(data->infile, O_RDONLY, 644);//error open
	}
	else if (token->type == HERE)
	{
		write_tmp(data);
		data->fd_infile = open(".here_doc", O_RDONLY, 644);
		data->delimiter = token->next;
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		data->outfile = token->next->content;
		if (token->type == RD_OUT)
			data->fd_outfile = open(data->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 644);
		else
			data->fd_outfile = open(data->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 644);
	}
	return (token->next->next);
}
