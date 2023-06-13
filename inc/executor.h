/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:30 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/13 14:12:05 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "mshell_types.h"

		//////////////////////
		/// exec_builtin.c ///
		//////////////////////

/*
Executes a builtin.
*/
int		exec_builtin(t_data *data, int proc_idx);

		/////////////////////
		/// exec_native.c ///
		/////////////////////

/*
Executes a program using execve.
*/
void	exec_native(t_data *data, int proc_idx, char **env);

		//////////////
		/// exec.c ///
		//////////////

int		exec_cmd_line(t_data *data);

		////////////////
		/// exec_2.c ///
		////////////////

void	exec_open_files(t_data *data, int proc_idx);

		/////////////////////
		// files_manager.c //
		/////////////////////

void	check_open_error(int fd, t_cmd *cmd);
void	open_files(t_cmd *cmd);
void	close_files(t_cmd *cmd);

		////////////////
		// here_doc.c //
		////////////////

int		input_heredoc(t_cmd *cmd, t_data *data);

		//////////////////
		/// pipe_dup.c ///
		//////////////////

void	open_pipe(t_data *data);
void	close_pipe(t_data *data);
void	dup_in_out(int fd_in, int fd_out);
void	dup_pipe(t_data *data, int proc_idx);
void	dup_file(t_data *data, int proc_idx);

#endif
