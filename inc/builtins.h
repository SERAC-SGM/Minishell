/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:43:27 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/17 12:58:46 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "mshell_types.h"

int		ft_cd(char **attr, t_data *data);
int		ft_echo(char **attr);
void	ft_env(t_list *env, char **attr);
int		ft_pwd(void);
void	ft_export(char	**args, t_list *env, t_list *set);
int		ft_unset(char **attr, t_data *data);
void	ft_exit(void);

#endif