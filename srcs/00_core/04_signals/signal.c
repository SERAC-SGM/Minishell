/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 15:07:05 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler(int signo)
{
	if (signo == SIGINT)
		sig_int();
	if (signo == SIGQUIT)
		sig_quit();
}

void	init_sig(void)
{
	g_sig.sig_int = 0;
	g_sig.sig_quit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}

/*

*/
void	enable_signal(void)
{
	struct sigaction	act;

	init_sig();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGQUIT, &act, NULL);
	sigaction(SIGINT, &act, NULL);
}
