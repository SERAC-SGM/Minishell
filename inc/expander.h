/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:25 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 17:03:42 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "mshell_types.h"

void	expand(t_tkn_lst *token, t_list *env);
void	expand_tokenize(t_tkn_lst *token, t_list *env);

#endif
