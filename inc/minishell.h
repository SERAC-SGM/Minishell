/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 14:35:14 by maaliber         ###   ########.fr       */
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
	char	*name; // = data[0]
	char	**args; // = ++data
	char	*path;
}	t_funct;

typedef struct s_redirect
{
	char	*filepath; // NULL si pipe, input, error ou output
	int		fd;
	int		type; // < == 0, << == 1 here_doc, > = 2 Overwrite, 3 = >> APPEND
}	t_redirect;

/*Stack structure - Chained list with index and run number*/
typedef struct s_cmd
{
	int				cmd_no;
	int				pid;
	struct s_funct	*fct;
	int				ret;
	int				in;
	int				out;
}	t_cmd;

/*Stack structure - Chained list with index and run number*/
typedef struct s_data
{
	int				fd_env;
	int				fd_history;
	int				nb_process;
	struct s_cmd	cmds[CMD_MAX];
	int				fd[OPEN_MAX];
	int				exit_status;
}	t_data;

#endif
