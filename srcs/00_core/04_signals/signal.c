/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/16 15:37:09 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig = { 0, 0, 0, 0, 0 };

void	handler(int signo)
{
	if (signo == SIGINT)
		sig_int();
	if (signo == SIGQUIT)
		sig_quit();
}

/**/
void	enable_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}
