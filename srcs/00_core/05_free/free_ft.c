/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ft.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/22 15:29:42 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
