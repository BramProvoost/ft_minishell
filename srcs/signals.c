/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 14:12:42 by bprovoos          #+#    #+#             */
/*   Updated: 2023/03/27 13:43:38 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	sigint_ctr_c_handler(int signum)
{
	(void)signum;
	// rl_replace_line("", 0);
	ft_putchar_fd('\n', 2);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = 1;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_ctr_c_handler);
	signal(SIGQUIT, SIG_IGN);
}
