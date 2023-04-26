/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:01:58 by maaliber          #+#    #+#             */
/*   Updated: 2023/04/26 14:30:24 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <string.h>

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
	char	*opt;
	char	*path;
}	t_funct;

/*Stack structure - Chained list with index and run number*/
typedef struct s_ppx
{
	int				fd_in;
	int				fd_out;
	char			**env_path;
	int				nb_process;
	struct s_funct	**cmds;
	int				fd[OPEN_MAX];
	int				here;
	char			*lim;
}	t_ppx;

/*Utilised functions*/
void	print_cmds(t_funct **cmds);
void	print_ppx_info(t_ppx *info);

/*Free functions*/
void	free_funct(t_funct *funct);
void	free_cmds(t_funct **cmds);
void	free_ppx(t_ppx *ppx_info);

/*Error functions*/
void	msg_error(int err_id, char *item);
void	exit_error(int err_id, char *item, t_ppx *info);

/*Parsing functions*/
t_funct	**init_cmds(char **cmds_line, int nb_proc);
char	**get_envpath(char **env);
t_ppx	*init_ppx(int ac, char **av, char **env);
t_ppx	*parse_arg(int ac, char **av, char **env);

/*File descriptors functions*/
void	dup_in_out(int fd_in, int fd_out);
void	close_pipe(t_ppx *info);
void	open_pipe(t_ppx *info);

/*Input | Output functions*/
int		here_doc(char *lim, t_ppx *info);
void	open_infile(char *infile, t_ppx *info);
void	open_outfile(char *outfile, t_ppx *info);

/*Main functions*/
void	process(int p_no, t_ppx *info, char **env);
int		main(int ac, char **av, char **env);

#endif