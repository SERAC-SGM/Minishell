/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/03 12:49:24 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHEL_H

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

#define OPEN_MAX 4096
#define CMD_MAX (OPEN_MAX + 1)


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
	E_HEREDOC
};
typedef enum e_config_error	t_config_error;

/*
• *name (data[0]): name of the command.
• **args (data[1, ..., n]): optional arguments.
• *path: path to the command.
*/
typedef struct s_single_cmd
{
	char	**data;
	char	*name;
	char	**args;
	char	*path;
}	t_single_cmd;

/*Stack structure - Linked list with index and run number*/
typedef struct s_cmd
{
	int				cmd_number;
	int				pid;
	t_single_cmd	*cmd;
	int				return_value;
	int				in;
	int				out;
}	t_cmd;

/*
• *filepath: NULL if pipe, input, output or error
• type:
.   <:    0 (read from)
.   <<:   1 (here_doc)
.   >:    2 (overwrite - O_TRUNC)
.   >>:   3 (append - O_APPEND)
*/
typedef struct s_redirect
{
	char	*filepath;
	int		fd;
	int		type;
}	t_redirect;

/*Stack structure - Linked list with index and run number*/
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
