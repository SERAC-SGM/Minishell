/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:55 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 16:30:51 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mshell_types.h"

///////////////////////
// files-managment.c //
///////////////////////
/*
Creates a temporary .here_doc file and writes the user input.
*/
//void	write_tmp(t_cmd *cmd)
/*
Checks that the previous file is not a standard stream and closes it.
*/
//void		close_previous_file(t_data *data, t_tkn_lst *token);
/*
When encountering a file-related token (< << > >>), creates or overwrite the
corresponding infile or outfile. If the previous file is not a standard stream, 
it's closed before assigning the new file.
Returns the next special token.
If no non-special token is found, returns an error.
*/
t_tkn_lst	*handle_files(t_tkn_lst *token, t_cmd *cmd);

//////////////
// parser.c //
//////////////
void		parser(t_tkn_lst *token, t_data *data);

#endif
