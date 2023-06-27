/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:55 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/27 18:29:38 by maaliber         ###   ########.fr       */
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

////////////////
/// parser.c ///
////////////////

int		parser(t_data *data);

#endif
