/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/05 16:04:23 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "expander.h"
# include "executor.h"
# include "builtins.h"

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

/*
Defines a command, its 
*/
typedef struct s_cmd
{
	int				proc_idx;
	int				arg_count;
	int				pid;
	char			**cmd;
	int				return_value;
	int				in;//last in
	int				out;//last out
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
	int				cmd_count;
	struct s_cmd	command_list[CMD_MAX];
	int				fd[OPEN_MAX];
	char			*infile;
	int				fd_infile;
	char			*outfile;
	int				fd_outfile;
	int				outfile_mode;
	int				here_doc;
	int				status;
	int				exit;
}	t_data;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *nnew);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

#endif
