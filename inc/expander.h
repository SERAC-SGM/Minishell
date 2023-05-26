/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:25 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/26 17:08:24 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "mshell_types.h"

		//////////////
		//expander.c//
		//////////////

void	expand(char **content, t_list *env);

		////////////////////
		//expander_utils.c//
		////////////////////
/*
Returns the word length (delimited by spaces). If the expander flag is present,
non-alphanumeric characters are also used as delimiters.
*/
int		word_len(char *str, int expander);
/*
Duplicates (with malloc) the string passed as argument.
*/
char	*cpy_word(char *str);

#endif
