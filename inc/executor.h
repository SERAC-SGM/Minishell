/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:30 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/22 16:33:08 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "mshell_types.h"

void	open_pipe(t_data *data);
void	close_pipe(t_data *data);
void	dup_in_out(int fd_in, int fd_out);
void	dup_fds(t_data *data, int proc_idx);
int		exec_builtin(t_data *data, int proc_idx);
void	exec_native(t_data *data, int proc_idx, char **env);
int		exec_cmd_line(t_data *data);

		//////////////
		//here_doc.c//
		//////////////

int		input_heredoc(t_cmd *cmd);

		///////////////////
		//files_manager.c//
		///////////////////

void	check_open_error(int fd, t_cmd *cmd);
void	open_files(t_cmd *cmd);
void	close_files(t_cmd *cmd);

#endif
