/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:57:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/22 18:12:06 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Errors descriptions.
*/
struct s_errdesc
{
	int		code;
	char	*msg;
	int		err_no;
} errdesc[] = {
	{E_SUCCESS, "No error", 0},
	{E_STD, 0, 0},
	{E_NOMSG, 0, 0},
	{E_MEM, "memory allocation error\n", 0},
	{E_TOKEN, "syntax error near unexpected token", 2},
	{E_FILE, ": No such file or directory\n", 127},
	{E_DIR, ": Is a directory\n", 126},
	{E_PERM, ": permission denied\n", 1},
	{E_ARG, "invalid number of arguments\n", 1},
	{E_TOO_FEW_ARG, "invalid number of arguments\n", 1},
	{E_TOO_MANY_ARG, ": too many arguments\n", 1},
	{E_PIPE, "pipe\n", 0},
	{E_FORK, "fork\n", 0},
	{E_ENV, "environment\n", 0},
	{E_CMD_NOT_FOUND, ": command not found\n", 127},
	{E_HOME_NOT_SET, ": HOME not set\n", 1},
	{E_INVALID_ID, ": not a valid identifier\n", 1},
	{E_HEREDOC,
	"\nminishell: warning: here-document delimited by end-of-file, (wanted `",
			0},
};

void	error_msg(int err_id, char *item)
{
	char	*error_message;

	if (item)
		error_message = ft_strjoin(item, errdesc[err_id].msg);
	else
		error_message = ft_strdup(errdesc[err_id].msg);
	if (!error_message)
		return ;
	ft_putstr_fd(error_message, 2);
	free(error_message);
	g_sig.error_status = errdesc[err_id].err_no;
}

void	error_msg_cmd(int err_id, char *prefix, char *item)
{
	char	*error_message;
	char	*append;

	append = NULL;
	if (prefix && item)
		append = ft_strjoin(prefix, item);
	else if (item)
		append = ft_strdup(item);
	else if (prefix)
		append = ft_strdup(prefix);
	error_message = ft_strjoin_dup1(append, errdesc[err_id].msg);
	if (!error_message)
		return ;
	ft_putstr_fd(error_message, 2);
	free(error_message);
	g_sig.error_status = errdesc[err_id].err_no;
}

void	exit_error(int err_id, char *item, t_data *data)
{
	char	*error_message;
	int		i;

	if (err_id == E_STD)
		perror("");
	else if (err_id != E_NOMSG)
	{
		if (item)
			error_message = ft_strjoin(item, errdesc[err_id].msg);
		else
			error_message = ft_strdup(errdesc[err_id].msg);
		if (!error_message)
			return ;
		ft_putstr_fd(error_message, 2);
		free(error_message);
	}
	i = -1;
	while (++i < data->process_nb)
		close_files(&data->cmds_tab[i]);
	close_pipe(data);
	free_infile(data, data->process_nb);
	clear_data(data);
	g_sig.error_status = errdesc[err_id].err_no;
	exit(g_sig.error_status);
}
