/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 14:02:12 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define RD_IN 11
# define HERE 12
# define RD_OUT 21
# define APPEND 22
# define PIPE 30

/*
•type:
.RD_IN
.HERE
.RD_OUT
.APPEND
.PIPE
*/
typedef struct s_tkn_lst
{
	char		*content;
	int			type;
	t_tkn_lst	*next;
}	t_tkn_lst;

t_tkn_lst	*lexer(t_data *data);

#endif
