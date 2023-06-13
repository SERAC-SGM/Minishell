/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:25 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/13 12:36:34 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "mshell_types.h"

/*
Get variable name (with malloc) from the string passed as argument.
*/
char	*cpy_var(char *str);

/*
Expand variable followed by $ in format by the corresponding valueue in env
• $ is not iterpreted when into single quote
*/
void	expand(char **content, t_list *env);

#endif
