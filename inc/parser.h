/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:55 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/02 20:14:31 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//////////////
// parser.c //
//////////////

int	parsing_error(t_tkn_lst *token);
int	parser(t_tkn_lst *token, t_data *data);

#endif
