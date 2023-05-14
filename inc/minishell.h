/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 15:03:21 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "mshell_types.h"
# include "core.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"

/*
Trims character of str at the start and end of the string
*/
void	trim_char(char **str, char c);
char	*ft_strjoin_dup1(char *s1, char *s2);
void	init_env(t_data *data, char *env[]);
void	reset_data(t_data *data);

extern t_sig	g_sig;

#endif
