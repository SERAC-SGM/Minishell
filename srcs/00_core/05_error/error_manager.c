/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:57:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/24 12:30:41 by lletourn         ###   ########.fr       */
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
} errdesc[] = {
	{E_SUCCESS, "No error"},
	{E_STD, 0},
	{E_NOMSG, 0},
	{E_MEM, "memory allocation error\n"},
	{E_TOKEN, "syntax error near unexpected token\n"},
	{E_FILE, ": No such file or directory\n"},
	{E_PERM, ": permission denied\n"},
	{E_ARG, "invalid number of arguments\n"},
	{E_TOO_FEW_ARG, "invalid number of arguments\n"},
	{E_TOO_MANY_ARG, ": too many arguments\n"},
	{E_PIPE, "pipe\n"},
	{E_FORK, "fork\n"},
	{E_ENV, "environment\n"},
	{E_CMD_NOT_FOUND, ": command not found\n"},
	{E_HEREDOC, "here_doc\n"},
};

void	error_msg(int error_id, char *item, t_data *data)
{
	char	*error_message;

	(void)data;
	if (item)
		error_message = ft_strjoin(item, errdesc[error_id].msg);
	else
		error_message = ft_strdup(errdesc[error_id].msg);
	if (!error_message)
		return ;
	ft_putstr_fd(error_message, 2);
	free(error_message);
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
	clear_data(data);
	exit(g_sig.error_status);
}
