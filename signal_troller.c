/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_troller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaliber <maaliber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 18:25:51 by maaliber          #+#    #+#             */
/*   Updated: 2023/05/30 18:28:26 by maaliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>

void	sigint_handler(int signum)
{
	(void)signum;
	printf("SIGINT !!!\n");
}

void	sigquit_handler(int signum)
{
	(void)signum;
	printf("SIGQUIT !!!\n");	
}

int	main(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (1)
	{

	}
}