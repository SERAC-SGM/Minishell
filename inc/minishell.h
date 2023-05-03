/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 11:47:35 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"

enum e_config_error
{
	E_SUCCESS = 0,
	E_STD,
	E_NOMSG,
	E_FILE,
	E_PERM,
	E_ARG,
	E_PIPE,
	E_FORK,
	E_ENV,
	E_CMD,
	E_HEREDOC,
};

typedef enum e_config_error	t_error;

typedef struct s_funct
{
	char	**data;
	char	*name;
	char	*args;
	char	*path;
}	t_funct;

/*Stack structure - Chained list with index and run number*/
typedef struct s_cmd
{
	int				idx;
	int				pid;
	struct s_funct	*ft;
	int				ret;
	int				in;
	int				out;
}	t_cmd;

/*Stack structure - Chained list with index and run number*/
typedef struct s_data
{
	char			**env;
	int				env_local;
	int				nb_process;
	struct s_cmd	**cmds;
	int				fd[OPEN_MAX];
}	t_data;

#endif