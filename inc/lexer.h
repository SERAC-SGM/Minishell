/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 12:50:16 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define RD_IN 11
# define HERE 12
# define RD_OUT 21
# define APPEND 22
# define PIPE 30

typedef struct s_tkn_lst
{
	char		*content;
	int			type; // 0: Regular entry, 1: Single quoted string, 2: Double quoted string
	t_tkn_lst	*next;
}	t_tkn_lst;

t_tkn_lst	*new_token(char	*str, int type);
t_tkn_lst	*last_token(t_tkn_lst *tk_list);
void		add_back_token(t_tkn_lst **tk_list, t_tkn_lst *token);
void		del1_token(t_tkn_lst *token);
void		clear_token_list(t_tkn_lst **tk_list);

t_tkn_lst	*lexer(t_data *data);

#endif