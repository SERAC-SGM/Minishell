/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:30 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 15:12:00 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "mshell_types.h"

void	open_pipe(t_data *data);
void	close_pipe(t_data *data);
void	dup_in_out(int fd_in, int fd_out);
void	dup_pipe(t_data *data, int proc_idx);
int		exec_builtin(t_data *data, int proc_idx);
void	exec_native(t_data *data, int proc_idx, char **env);
int		exec_cmd_line(t_data *data);

#endif
