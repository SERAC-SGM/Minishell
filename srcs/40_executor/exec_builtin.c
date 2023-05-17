/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:36 by lletourn          #+#    #+#             */
/*   Updated: 2023/05/17 12:59:39 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_data *data, int proc_idx)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "echo") == 0)
		ret = ft_echo(data->cmds_tab[proc_idx].attr);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "cd") == 0)
		ret = ft_cd(data->cmds_tab[proc_idx].attr, data);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "pwd") == 0)
		ret = ft_pwd();
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "env") == 0)
		ft_env(data->env, data->cmds_tab[proc_idx].attr);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "export") == 0)
		ft_export(data->cmds_tab[proc_idx].attr, data->env, data->set);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "unset") == 0)
		ft_unset(data->cmds_tab[proc_idx].attr, data);
	if (ft_strcmp(data->cmds_tab[proc_idx].attr[0], "exit") == 0)
		ft_exit();
	return (ret);
}
