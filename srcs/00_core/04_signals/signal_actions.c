/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:40:53 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/17 16:45:55 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(void)
{
	if (g_sig.pid != 0) //parent_process
	{
		write(2, "\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_sig.exit_status = 130;
	}
	else
		exit(0);
}

void	sig_quit(void)
{
	if (g_sig.pid != 0) //parent_process
		return ;
	else
		exit(0);
}
