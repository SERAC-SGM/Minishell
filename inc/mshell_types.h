/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:38:57 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 19:39:29 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_TYPES_H
# define MSHELL_TYPES_H

# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RD_IN 11
# define HERE 12
# define RD_OUT 21
# define APPEND 22
# define PIPE 30
# define END 127
//# define OPEN_MAX 1024 //ALREADY DEFINED IN LIBFT.H
# define CMD_MAX 1024

enum e_config_error
{
	E_SUCCESS = 0,
	E_STD,
	E_NOMSG,
	E_MEM,
	E_TOKEN,
	E_FILE,
	E_PERM,
	E_ARG,
	E_TOO_FEW_ARG,
	E_TOO_MANY_ARG,
	E_PIPE,
	E_FORK,
	E_ENV,
	E_CMD,
	E_HEREDOC
};
typedef enum e_config_error	t_config_error;

/*
Everything required to run a command.
• process_index: index of the current process.
• pid: PID of the current process.
• arg_count: number of arguments.
• *cmd[args] : 2-dimensional array containing each command and its
arguments (cmd[i][0] : path of the command, cmd[i][j] : optional arguments).
• infile: name of the infile.
• fd_infile: fd of the infile.
• outfile: name of the outfile.
• fd_outfile: fd of the outfile.
• here_doc: indicates the presence of a here_document.
• delimiter: delimiter in case of here_document.
*/
typedef struct s_cmd
{
	int		process_index;
	int		arg_count;
	char	**attr;
	char	*infile;
	int		fd_in;
	int		here_doc;
	char	*outfile;
	int		fd_out;
	int		append;
	char	*delimiter;
}			t_cmd;

/*
Token structure.
• type:
.   <:    0 (read from)
.   <<:   1 (here_doc)
.   >:    2 (overwrite - O_TRUNC)
.   >>:   3 (append - O_APPEND)
*/
typedef struct s_tkn_lst
{
	char				*content;
	int					type;
	struct s_tkn_lst	*next;
}	t_tkn_lst;

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}	t_list;

/*
Data structure.
*/
typedef struct s_data
{
	t_list			*env;
	t_tkn_lst		*token_list;
	t_list			*set;
	char			**env_path;
	HIST_ENTRY		**hist;
	char			*cmd_line;
	int				process_nb;
	struct s_cmd	cmds_tab[CMD_MAX];
	int				fd[OPEN_MAX];
	int				status;
	int				exit;
}	t_data;

/*
Global signal structure
*/
typedef struct	s_sig
{
	int				sig_int;
	int				sig_quit;
	int				exit_status;
	pid_t			pid;
}	t_sig;

#endif
