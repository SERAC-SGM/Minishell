/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:27 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 17:59:25 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "mshell_types.h"

int		cd(char **attr, t_data *data);
int		echo(char **attr);
void	env(t_list *env, char **attr);
int		pwd(void);
void	export(char	**args, t_list *env, t_list *set);
int		unset(char **attr, t_data *data);

#endif