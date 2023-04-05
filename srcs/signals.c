/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signals.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/01 14:12:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/04/05 17:54:10 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	sigint_ctr_c_handler(int signum)
{
	(void)signum;
	rl_replace_line("", 0);
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = 1;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_ctr_c_handler);
	signal(SIGQUIT, SIG_IGN);
}
