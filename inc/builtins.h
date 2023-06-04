/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:27 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/04 19:45:55 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "mshell_types.h"

int		ft_cd(char **args, t_data *data);
int		ft_echo(char **args);
void	ft_env(t_list *env, char **args);
int		ft_pwd(void);
void	ft_export(char	**args, t_data *data);
int		ft_unset(char **args, t_data *data);
void	ft_exit(void);

#endif
