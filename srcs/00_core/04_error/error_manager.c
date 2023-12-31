/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:57:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/30 17:19:28 by lletourn         ###   ########.fr       */
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
	{E_FILE, ": No such file or directory\n", 1},
	{E_DIR, ": Is a directory\n", 126},
	{E_PERM, ": permission denied\n", 1},
	{E_ARG, "invalid number of arguments\n", 1},
	{E_TOO_FEW_ARG, "invalid number of arguments\n", 1},
	{E_TOO_MANY_ARG, "too many arguments\n", 1},
	{E_PIPE, "pipe\n", 0},
	{E_FORK, "fork\n", 0},
	{E_ENV, "environment\n", 0},
	{E_FILE_CMD, ": No such file or directory\n", 127},
	{E_CMD_NOT_FOUND, ": command not found\n", 127},
	{E_HOME_NOT_SET, "HOME not set\n", 1},
	{E_INVALID_ID, "': not a valid identifier\n", 1},
	{E_HEREDOC,
	"\nminishell: warning: here-document delimited by end-of-file, (wanted `",
			0},
	{E_NUMERIC_ARG,
	": numeric argument required\n", 2},
	{E_INVALID_OPTION,
	": invalid option\n", 2}
};

void	error_msg(int err_id, char *item)
{
	char	*error_message;
	char	*output;

	if (item)
		error_message = ft_strjoin(item, errdesc[err_id].msg);
	else
		error_message = ft_strdup(errdesc[err_id].msg);
	if (!error_message)
		return ;
	output = ft_strjoin("minishell: ", error_message);
	free(error_message);
	ft_putstr_fd(output, 2);
	free(output);
}

void	error_msg_cmd(int err_id, char *prefix, char *item)
{
	char	*error_message;
	char	*append;
	char	*output;

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
	output = ft_strjoin("minishell: ", error_message);
	free(error_message);
	ft_putstr_fd(output, 2);
	free(output);
	g_sig.error_status = errdesc[err_id].err_no;
}

void	exit_error(int err_id, char *item, t_data *data)
{
	char	*error_message;

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
	close_all_files(data);
	close_pipe(data);
	free_infile(data, data->process_nb);
	clear_data(data);
	if (err_id != E_NOMSG)
		g_sig.error_status = errdesc[err_id].err_no;
	exit(g_sig.error_status);
}
