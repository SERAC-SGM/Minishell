/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:25 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/06 11:50:08 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "mshell_types.h"

		//////////////
		//expander.c//
		//////////////

/*
Get variable name (with malloc) from the string passed as argument.
*/
char	*cpy_var(char *str);

void	expand(char **content, t_list *env);

#endif
