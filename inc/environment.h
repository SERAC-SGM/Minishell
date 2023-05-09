/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:24:07 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/09 15:41:18 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "mshell_types.h"

char	*get_var_value(char *name, t_list *env);
void	set_env_var(char *name, char *val, t_list *env);


#endif