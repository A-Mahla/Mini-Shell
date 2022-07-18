/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meudier <meudier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:15:50 by meudier           #+#    #+#             */
/*   Updated: 2022/07/18 17:24:09 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void handler_sigint(int sig)
{
	if (sig == SIGINT)
	{
        write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();		
//		kill(getpid(), SIGCONT);
	}
}

void	sig_init(void)
{
	struct sigaction sa;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = &handler_sigint;
	sigaction(SIGINT, &sa, NULL);
}
