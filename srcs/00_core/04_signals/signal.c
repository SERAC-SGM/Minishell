/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/23 14:03:58 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig = {0, 0, 1};

void	handler(int signo)
{
	if (signo == SIGINT)
		sig_int();
	if (signo == SIGQUIT)
		sig_quit();
}

void	update_signal(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
}

void	enable_signal(void)
{
	struct sigaction	act1;
	struct sigaction	act2;

	ft_memset(&act1, 0, sizeof(act1));
	ft_memset(&act2, 0, sizeof(act2));
	act1.sa_handler = &handler;
	act2.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act1, NULL);
	sigaction(SIGQUIT, &act2, NULL);
}
