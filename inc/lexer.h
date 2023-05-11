/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 15:51:48 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "mshell_types.h"

/*
If content is NULL pointer the token is a special character
•type:
.    RD_IN
.    HERE
.    RD_OUT
.    APPEND
.    PIPE
*/	
int			is_special(char *str);
int			set_mode(char *cmd_l);
t_tkn_lst	*new_token(char	*str, int type);
t_tkn_lst	*last_token(t_tkn_lst *tk_list);
void		add_back_token(t_tkn_lst **tk_list, t_tkn_lst *token);
void		del1_token(t_tkn_lst *token);
void		clear_token_list(t_tkn_lst **tk_list);
char		*standard_mode(char **str, t_list *env);
char		*single_quote_mode(char **str);
char		*double_quote_mode(char **str, t_list *env);

t_tkn_lst	*tokenize(char **cmd_line, t_list *env);
t_tkn_lst	*lexer(t_data *data);

#endif
