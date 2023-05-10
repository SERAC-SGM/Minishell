/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:24:07 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 12:38:07 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "mshell_types.h"

char	*get_var_value(char *name, t_list *env);
void	set_env_var(char *name, char *val, t_list *env);

#endif
