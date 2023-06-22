/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/06/22 15:51:03 by maaliber         ###   ########.fr       */
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
			// ft_printf("INDEX:%d->%s:%d\n", data->cmds_tab[proc_idx].process_index, data->cmds_tab[proc_idx].infile, data->cmds_tab[proc_idx].fd_in);
			if (data->cmds_tab[i].fd_in > 2)
				close(data->cmds_tab[i].fd_in);
			free(data->cmds_tab[i].infile);
		}
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
