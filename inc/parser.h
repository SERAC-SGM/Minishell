/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:55 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/23 14:42:43 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

////////////////
/// parser.c ///
////////////////

t_tkn_lst	*parse_type(t_data *data, t_tkn_lst *token, int *proc_idx);

///////////////////////
/// parsing_error.c ///
///////////////////////

/*
pose pas de questions
*/
void		norminette_bypass_3000(t_tkn_lst *token, t_cmd *cmd);
int			parsing_error(t_tkn_lst *token);
int			parser(t_data *data);

#endif
