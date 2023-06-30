/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 18:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/28 23:02:14 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# include "mshell_types.h"

/////////////////////
// close_files.c //
/////////////////////

void	free_infile(t_data *data, int proc_idx);
void	unlink_heredoc(t_cmd *cmd);
void	close_files(t_cmd *cmd);
void	close_all_files(t_data *data);

/////////////////////
// open_files.c //
/////////////////////

void	open_files(t_cmd *cmd);
void	open_all_files(t_data *data);

////////////////
// here_doc.c //
////////////////

int		input_heredoc(t_cmd *cmd, t_data *data);

/////////////////////
/// redirection.c ///
/////////////////////

/*
When encountering a redirection token (< << > >>), assings the correct
following filename to the command structure.
If no filemame or no non-special after the filename token is found,
returns 0.
*/
void	redirection(t_tkn_lst *token, t_cmd *cmd, t_data *data, int reset);

#endif
