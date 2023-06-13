/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 12:58:43 by lletourn          #+#    #+#             */
/*   Updated: 2023/06/13 14:09:24 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_open_files(t_data *data, int proc_idx)
{
	if (data->cmds_tab[proc_idx].here_doc)
	{
		if (!input_heredoc(&data->cmds_tab[proc_idx], data))
			data->cmds_tab[proc_idx].here_doc = -1;
	}
	open_files(&data->cmds_tab[proc_idx]);
}
