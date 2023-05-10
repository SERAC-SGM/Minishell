/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:07:41 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/09 16:28:51 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	write_tmp(t_cmd *cmd)
// {
// 	char	*line;

// 	cmd->fd_infile = open(".here_doc", O_WRONLY | O_CREAT | O_EXCL, 0644);
// 	// if (cmd->fd_infile == -1)
// 	// 	ft_exit(data, NULL, 0, 0);
// 	line = "";
// 	ft_printf("heredoc> ", 1);
// 	while (1)
// 	{
// 		line = get_next_line(0);
// 		if (line == NULL)
// 			break ;
// 		if (ft_strlen(cmd->delimiter) + 1 == ft_strlen(line)
// 			&& !ft_strncmp(line, cmd->delimiter, ft_strlen(cmd->delimiter)))
// 		{
// 			close(cmd->fd_infile);
// 			close(0);
// 		}
// 		else
// 		{
// 			ft_printf("heredoc> ", 1);
// 			write(cmd->fd_infile, line, ft_strlen(line));
// 		}
// 		free(line);
// 	}
// }

// void	close_previous_file(t_cmd *cmd, t_tkn_lst *token)
// {
// 	if (token->type == RD_IN || token->type == HERE)
// 	{
// 		if (data->fd_infile != 0)
// 			close(data->fd_infile);
// 	}
// 	else if (token->type == RD_OUT || token->type == APPEND)
// 	{
// 		if (data->fd_outfile != 1)
// 			close(data->fd_outfile);
// 	}
// }

t_tkn_lst	*handle_files(t_tkn_lst *token, t_cmd *cmd)
{
	if ((!token->next->content))
		printf("syntax error near unexpected token `XXX'\n");
	//close_previous_file(data, token);
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
