/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/22 17:13:05 by lletourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_infile(t_data *data, int proc_idx)
{
	int	i;

	i = -1;
	while (++i <= proc_idx)
	{
		if (data->cmds_tab[i].infile)
		{

			if (data->cmds_tab[i].fd_in > 2)
				close(data->cmds_tab[i].fd_in);
			free(data->cmds_tab[i].infile);
		}
		if (data->cmds_tab[i].infile_hdoc)
			free(data->cmds_tab[i].infile_hdoc);
	}
}

void	clear_data(t_data *data)
{
	reset_data(data);
	free_tab(data->env_path);
	ft_lstclear(&data->env);
	ft_lstclear(&data->set);
}

void	clear_exit(t_data *data)
{
	rl_clear_history();
	close_pipe(data);
	clear_data(data);
	exit(g_sig.error_status);
}
