/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_pids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:27:56 by edawood           #+#    #+#             */
/*   Updated: 2023/03/27 14:00:45 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	wait_for_pids(pid_t pid)
{
	int				return_wait;

	if (pid != ERROR)
		waitpid(pid, &return_wait, 0);
	while (wait(NULL) != ERROR)
		;
	if (pid != ERROR)
	{
		if (!WIFSIGNALED (return_wait))
			g_exit_code = WEXITSTATUS (return_wait);
		else if (WIFSIGNALED (return_wait) && g_exit_code == 131)
			write(STDERR, "Quit: 3\n", 9);
		else if (WIFSIGNALED (return_wait) && g_exit_code == 130)
			write(1, "\n", 1);
	}
}
