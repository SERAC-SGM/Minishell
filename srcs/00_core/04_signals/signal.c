/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lletourn <lletourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:57:15 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/24 12:27:55 by lletourn         ###   ########.fr       */
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
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = &handler;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGQUIT, &action, NULL);
}

void	enable_signal(void)
{
	struct sigaction	action1;
	struct sigaction	action2;

	ft_memset(&action1, 0, sizeof(action1));
	ft_memset(&action2, 0, sizeof(action2));
	action1.sa_handler = &handler;
	action2.sa_handler = SIG_IGN;
	sigaction(SIGINT, &action1, NULL);
	sigaction(SIGQUIT, &action2, NULL);
}
