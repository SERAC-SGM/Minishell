/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:27 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/27 11:46:51 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "mshell_types.h"

int		ft_cd(char **args, t_data *data);
int		ft_echo(char **args);
void	ft_env(t_list *env, char **args);
int		ft_pwd(char **args, t_data *data);
int		ft_export(char **args, t_data *data);
int		ft_unset(char **args, t_data *data);
int		ft_exit(char **args);

#endif
