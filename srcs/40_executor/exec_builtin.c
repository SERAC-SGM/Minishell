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
	int		ret;

	ret = 0;
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "echo") == 0)
		ret = echo(data->cmds_tab[proc_idx].attr);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "cd") == 0)
		ret = cd(data->cmds_tab[proc_idx].attr);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "pwd") == 0)
		ret = pwd();
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "env") == 0)
		env(data->env, data->cmds_tab[proc_idx].attr);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "export") == 0)
		export(data->cmds_tab[proc_idx].attr, data->env, data->set);
	return (ret);
}
