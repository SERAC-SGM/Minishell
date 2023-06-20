/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:34 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/13 12:34:07 by lletourn         ###   ########.fr       */
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

		////////////////////
		/// input_mode.c ///
		////////////////////

/*
Set mode - return value of mode used for generating token
• 1 if the first character is ' and ' is not unclosed
• 2 if the first character is " and " is not unclosed
• 0 otherwise
*/
int			set_mode(char *cmd_l);
/*
Create standard token :
• if it starts with a special character : |, <, <<, >, >>
• if it's a standard entry : mode 0
• if it's in between single quote ['] : mode 1
• if it's in between double quote ["] : mode 2
*/
char		*standard_mode(char **str, t_list *env);
/*
Create single quote token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
char		*single_quote_mode(char **str);
/*
Create double quote token :
• if start with a special character : |, <, <<, >, >>
• if is a standard entry : mode 0 
• if is in between single quote ['] : mode 1 
• if is in between double quote ["] : mode 2
*/
char		*double_quote_mode(char **str, t_list *env);

		/////////////////////
		/// lexer_error.c ///
		/////////////////////

/*
Displays the "ambiguous redirect" error message.
*/
int			error_ambiguous(t_tkn_lst *token, char *cmd_l, t_data *data);

		////////////////////
		/// lexer_util.c ///
		////////////////////

/*
Checks if the string corresponds to any special character and returns the
matching value:
• <:  returns RD_IN
• <<: returns HERE
• >:  returns RD_OUT
• >>: returns APPEND
• |:  returns PIPE
• \n or \0: returns END
• returns 0 otherwise
*/
int			is_special(char *str);

		///////////////
		/// lexer.c ///
		///////////////

/*
Creates a token list from a command line passed as argument
Identifies special characters (|, ', ", <, <<, >, >>)
Mode :
0 = standard (interpreting everything)
1 = Single quote (interpreting nothing)
2 = double quote (interpreting nothing but $)
*/
void		lexer(t_data *data);

///////////////////
/// token_lst.c ///
///////////////////

/*
Allocates (with malloc) a new token list.
• content: string
• type:
*/
t_tkn_lst	*new_token(char	*str, int type);

/*
Get last token of the list
*/
t_tkn_lst	*last_token(t_tkn_lst *tk_list);

/*
Add a token or a token list at the end of an existing list,
if existing list is NULL return the list added
*/
void		add_back_token(t_tkn_lst **tk_list, t_tkn_lst *token);

/*
Delete 1 token
*/
void		del1_token(t_tkn_lst *token);

/*
Free and delete all content of the list
*/
void		clear_token_list(t_tkn_lst **tk_list);

///////////////
/// token.c ///
///////////////

/*
Creates token with command line with differents cases :
• if it starts with a special character : |, <, <<, >, >>
• if it's a standard entry : mode 0
• if it's between single quote ['] : mode 1
• if it's between double quote ["] : mode 2
*/
t_tkn_lst	*tokenize(char **cmd_line, t_list *env);

#endif
