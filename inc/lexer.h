/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 17:31:39 by lletourn         ###   ########.fr       */
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
If content is NULL pointer the token is a special character
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

t_tkn_lst	*new_token(char	*str, int type);
t_tkn_lst	*last_token(t_tkn_lst *tk_list);
void		add_back_token(t_tkn_lst **tk_list, t_tkn_lst *token);
void		del1_token(t_tkn_lst *token);
void		clear_token_list(t_tkn_lst **tk_list);
t_tkn_lst	*standard_token(char **str, t_list *env);
t_tkn_lst	*single_quote_token(char **str);
t_tkn_lst	*double_quote_token(char **str, t_list *env);
t_tkn_lst	*generate_token(char **cmd_line, int mode, t_list *env);
t_tkn_lst	*special_token(char **str);

t_tkn_lst	*lexer(t_data *data);

#endif
