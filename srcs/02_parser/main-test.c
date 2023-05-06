/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 12:02:59 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/06 12:04:08 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

#define RD_IN 11
#define HERE 12
#define RD_OUT 21
#define APPEND 22
#define PIPE 30
#define OPEN_MAX 4096
#define CMD_MAX 4097

typedef struct s_tkn_lst
{
	char				*content;
	int					type;
	struct s_tkn_lst	*next;
}	t_tkn_lst;

typedef struct s_cmd
{
	int				arg_count;
	int				pid;
	char			**cmd;
	int				return_value;
	int				in;
	int				out;
}	t_cmd;

typedef struct s_data
{
	//t_list			*env;
	//HIST_ENTRY		**hist;
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
	char			*delimiter;
	int				status;
	int				exit;
}	t_data;

int main(void)
{
	t_tkn_lst l1;
	t_tkn_lst l2;
	t_tkn_lst l3;
	t_tkn_lst l4;
	t_tkn_lst l5;
	t_tkn_lst l6;
	t_tkn_lst l7;
	t_tkn_lst l8;
	t_tkn_lst l9;
	t_tkn_lst l10;



	t_data data;
	data.cmd_count = 0;
	data.infile = NULL;
	data.fd_infile = 0;
	data.outfile = NULL;
	data.fd_outfile = 1;
	data.here_doc = 0;

	l1.content = 0;
	l1.type = RD_IN;
	l1.next = &l2;

	l2.content = "infile";
	l2.type = 0;
	l2.next = &l3;

	l3.content = "ls";
	l3.type = 2;
	l3.next = &l4;

	l4.content = "-l";
	l4.type = 3;
	l4.next = &l5;

	l5.content = NULL;
	l5.type = PIPE;
	l5.next = &l6;

	l6.content = "hostname";
	l6.type = 1;
	l6.next = &l7;

	l7.content = "-randomarg1";
	l7.type = 0;
	l7.next = &l8;

	l8.content = "-randomarg2";
	l8.type = 2;
	l8.next = &l9;

	l9.content = NULL;
	l9.type = APPEND;
	l9.next = &l10;

	l10.content = "outfile";
	l10.type = 2;
	l10.next = NULL;

	int i = -1;
	int	j = 0;
	parser(&l1, &data);
	printf("cmd count = %d\ninfile = %s (fd %d)\noutfile = %s (fd %d)\nhere_doc = %d\n", 
		data.cmd_count, data.infile, data.fd_infile, data.outfile, data.fd_outfile, data.here_doc);
	while (++i < data.cmd_count)
	{
		j = 0;
		printf("command[%d] = %s (arg count = %d)\n", i, data.command_list[i].cmd[0], data.command_list[i].arg_count);
		while (++j < data.command_list[i].arg_count)
			printf("arg[%d] = %s\n", i, data.command_list[i].cmd[j]);
		free(data.command_list[i].cmd);
	}
}
