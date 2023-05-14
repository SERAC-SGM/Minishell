/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:27 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 18:20:33 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "mshell_types.h"

int		cd(char **attr);
int		echo(char **attr);
void	env(t_list *env, char **attr);
int		pwd(void);
void	export(char	**args, t_list *env, t_list *set);

#endif