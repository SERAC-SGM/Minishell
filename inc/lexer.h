/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 15:37:12 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef struct s_tkn_lst
{
	char		*content;
	int			type; // 0: Regular entry, 1: Single quoted string, 2: Double quoted string, 3
	t_tkn_lst	*next;
}	t_tkn_lst;

t_tkn_lst	*lexer(char *cmd_line);

#endif