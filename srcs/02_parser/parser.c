/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 14:19:32 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/05 15:13:31 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
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
#include <stdlib.h>

# define RD_IN 11
# define HERE 12
# define RD_OUT 21
# define APPEND 22
# define PIPE 30

# define OPEN_MAX 4096
# define CMD_MAX 4097

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
	int				status;
	int				exit;
}	t_data;

/*
Creates a temporary .here_doc file and writes the user input.
*/
void	write_tmp(t_args *args)
{
	char	*line;

	args->fd_file1 = open(".here_doc", O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (args->fd_file1 == -1)
		ft_exit(args, NULL, 0, 0);
	line = "";
	ft_printf("heredoc> ", 1);
	while (1)
	{
		line = get_next_line(0);
		if (line == NULL)
			break ;
		if (ft_strlen(args->end) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, args->end, ft_strlen(args->end)))
		{
			close(args->fd_file1);
			close(0);
		}
		else
		{
			ft_printf("heredoc> ", 1);
			write(args->fd_file1, line, ft_strlen(line));
		}
		free(line);
	}
}

/*
Checks that the previous file is not a standard stream and closes it.
*/
void	close_previous_file(t_data *data, t_tkn_lst *token)
{
	if (token->type == RD_IN || token->type == HERE)
	{
		if (data->fd_infile != 0)
			close(data->fd_infile);
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		if (data->fd_outfile != 1)
			close(data->fd_outfile);
	}
}

/*
When encountering a file-related token (< << > >>), creates or overwrite the
corresponding infile or outfile. If the previous file is not a standard stream, 
it's closed before assigning the new file.
Returns the next special token.
If no non-special token is found, returns an error (except for <<, where this is
the opposite).
*/
t_tkn_lst	*handle_files(t_tkn_lst *token, t_data *data)
{
	if ((token->type != HERE && !token->next->content)
		|| (token->type == HERE && token->next->content))
		printf("syntax error near unexpected token `TOKEN->NEXT->CONTENT'\n");
	close_previous_file(data, token);
	if (token->type == RD_IN)
	{
		data->infile = token->next->content;
		data->fd_infile = open(data->infile, O_RDONLY, 644);
	}
	else if (token->type == HERE)
	{
		data->here_doc = 1;
		data->fd_infile = open(".here_doc", O_RDONLY, 644);
		return (token->next);
	}
	else if (token->type == RD_OUT || token->type == APPEND)
	{
		data->outfile = token->next->content;
		if (token->type == RD_OUT)
			data->fd_outfile = open(data->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 644);
		else
			data->fd_outfile = open(data->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 644);
	}
	return (token->next->next);
}

/*
Adds a new command in the data structure. The first token is used as the name of
the command, and all following non-special tokens as optional arguments.
Returns the next special token.
*/
t_tkn_lst	*add_command(t_tkn_lst *token, t_data *data)
{
	int	index;

	index = 0;
	data->command_list[data->cmd_count].cmd = malloc(sizeof(char *) * 100);
	data->command_list[data->cmd_count].cmd[index++] = token->content;
	token = token->next;
	while (token && token->content)
	{
		data->command_list[data->cmd_count].cmd[index++] = token->content;
		token = token->next;
	}
	data->command_list[data->cmd_count].arg_count = index;
	data->command_list[data->cmd_count].cmd[index] = NULL;
	data->cmd_count++;
	return (token);
}

void	parser(t_tkn_lst *token, t_data *data)
{
	if (token->type == PIPE)
		printf("syntax error near unexpected token `%s'\n", token->next->content);
	while (token)
	{
		if (token && token->content)
		{
			token = add_command(token, data);}
		else if (token && token->type == PIPE)
			token = add_command(token->next, data);
		else if (token && !token->content)
			token = handle_files(token, data);
		else if (token)
			token = token->next;
	}
}


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
