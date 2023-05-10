/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:55 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 14:25:22 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "mshell_types.h"

///////////////////////
// files-managment.c //
///////////////////////

/*
When encountering a file-related token (< << > >>), assings the correct
following filename to the command structure.
Returns the next token after the filename.
If no filemame or no non-special after the filename token is found,
returns an error.
*/
t_tkn_lst	*handle_files(t_tkn_lst *token, t_cmd *cmd);
/*
Creates a temporary .here_doc file and writes the user input.
*/
void		write_heredoc(t_cmd *cmd);
/*
Opens the files set in the command structure, and assigns the FDs accordingly.
Exits if encountering an error with open.
*/
void		open_files(t_cmd *cmd, t_data *data);

//////////////
// parser.c //
//////////////

void		parser(t_tkn_lst *token, t_data *data);

#endif
