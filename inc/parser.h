/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:55 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/27 11:19:38 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

///////////////////////
/// parsing_error.c ///
///////////////////////

/*
pose pas de questions
*/
int		parsing_error(t_tkn_lst *token);

/////////////////////
/// redirection.c ///
/////////////////////

/*
When encountering a redirection token (< << > >>), assings the correct
following filename to the command structure.
If no filemame or no non-special after the filename token is found,
returns 0.
*/
void	redirection(t_tkn_lst *token, t_cmd *cmd);

////////////////
/// parser.c ///
////////////////

int		parser(t_data *data);

#endif
