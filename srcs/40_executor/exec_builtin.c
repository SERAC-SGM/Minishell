/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:38:09 by maaliber            #+#    #+#             */
/*   Updated: 2023/05/13 17:38:10 by maaliber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		exec_builtin(t_data *data, int proc_idx)
{
	int		result;

	result = 0;
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "echo") == 0)
		result = echo(&data->cmds_tab[proc_idx].attr[1]);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "cd") == 0)
		result = cd(&data->cmds_tab[proc_idx].attr[1]);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "pwd") == 0)
		result = pwd();
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "env") == 0)
		env(data->env);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "export") == 0)
		export(args, data->env, data->set);
	return (result);
}
