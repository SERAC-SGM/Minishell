/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/04 14:13:48 by lletourn         ###   ########.fr       */
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

# define OPEN_MAX 4096
# define CMD_MAX 4097

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

/*Stack structure - Linked list with index and run number*/
typedef struct s_cmd
{
	int				cmd_number;
	int				pid;
	char			**cmd;
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
typedef struct s_file
{
	char	*filepath;
	int		fd;
	int		type;
}	t_file;

typedef struct s_list
{
	char	*line;
	t_list	*next;
}	t_list;

/*
Stack structure - Linked list with index and run number

*/
typedef struct s_data
{
	t_list			*env;
	HIST_ENTRY		**hist;
	char			*cmd_line;
	int				nb_process; //
	struct s_cmd	cmds[CMD_MAX];//
	int				fd[OPEN_MAX];//?
	char			*infile;//
	int				fd_infile;//?
	char			*outfile;//
	int				fd_outfile;//?
	int				status;
	int				exit;
}	t_data;

#endif
