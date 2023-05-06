/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_types.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:38:57 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/06 12:23:40 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_TYPES_H
# define MSHELL_TYPES_H

# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RD_IN 11
# define HERE 12
# define RD_OUT 21
# define APPEND 22
# define PIPE 30
# define OPEN_MAX 1000
# define CMD_MAX 1000

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
	int				process_index;
	int				arg_count;
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

typedef struct s_tkn_lst
{
	char				*content;
	int					type;
	struct s_tkn_lst	*next;
}	t_tkn_lst;

typedef struct s_file
{
	char	*filepath;
	int		fd;
	int		type;
}	t_file;

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}	t_list;

/*
Stack structure - Linked list with index and run number

*/
typedef struct s_data
{
	t_list			*env;
	HIST_ENTRY		**hist;
	char			*cmd_line;
	int				cmd_count;
	struct s_cmd	command_list[CMD_MAX];
	int				fd[OPEN_MAX];
	char			*infile;
	int				fd_infile;
	char			*outfile;
	int				fd_outfile;
	char			*delimiter;
	int				status;
	int				exit;
}	t_data;

#endif
