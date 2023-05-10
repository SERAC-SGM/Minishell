/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:40:53 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/10 17:46:12 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(void)
{
	if (g_sig.pid == 0) //parent_process
	{
		//to be completed
	}
	else //child_process
	{
		//to be completed
	}
	g_sig.sig_int = 1;
}

void	sig_quit(void)
{
	if (g_sig.pid == 0) //parent_process
	{
		//to be completed
	}
	else //child_process
	{
		//to be completed
	}
	g_sig.sig_quit = 1;
}
