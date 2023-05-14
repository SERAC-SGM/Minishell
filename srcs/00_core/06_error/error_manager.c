/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:57:22 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 19:39:53 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{E_FILE, ": no such file or directory\n"},
	{E_PERM, ": permission denied\n"},
	{E_ARG, "invalid number of arguments\n"},
	{E_TOO_FEW_ARG, "invalid number of arguments\n"},
	{E_TOO_MANY_ARG, "invalid number of arguments\n"},
	{E_PIPE, "pipe\n"},
	{E_FORK, "fork\n"},
	{E_ENV, "environment\n"},
	{E_CMD, ": command not found\n"},
	{E_HEREDOC, "here_doc\n"},
};

void	error_msg(int err_id, char *item, t_data *data)
{
	char	*err_msg;

	(void)data;
	if (item)
		err_msg = ft_strjoin(item, errdesc[err_id].msg);
	else
		err_msg = ft_strdup(errdesc[err_id].msg);
	if (!err_msg)
		return ;
	ft_putstr_fd(err_msg, 2);
	free(err_msg);
}

void	exit_error(int err_id, char *item, t_data *data)
{
	char	*err_msg;

	if (err_id == E_STD)
		perror("");
	else if (err_id != E_NOMSG)
	{
		if (item)
			err_msg = ft_strjoin(item, errdesc[err_id].msg);
		else
			err_msg = ft_strdup(errdesc[err_id].msg);
		if (!err_msg)
			return ;
		ft_putstr_fd(err_msg, 2);
		free(err_msg);
	}
	free_data(data);
	exit(1);
}