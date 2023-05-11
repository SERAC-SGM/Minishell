/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/11 15:37:56 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "mshell_types.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"
# include "history.h"
# include "error.h"
# include "signal.h"
# include "environment.h"
# include "utils.h"

/*
Trims character of str at the start and end of the string
*/
void	trim_char(char **str, char c);
char	*ft_strjoin_dup1(char *s1, char *s2);
void	init_env(t_data *data, char *env[]);

#endif
