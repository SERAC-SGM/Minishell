/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matnam <matnam@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/14 19:59:48 by matnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sig	g_sig = { 0, 0, 0, 0 };

// t_sig	init_sig(void)
// {
// 	t_sig sig;
	
// 	sig.sig_int = 0;
// 	sig.sig_quit = 0;
// 	sig.pid = 0;
// 	sig.exit_status = 0;
// 	return (sig);
// }

void handler(int signo)
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
