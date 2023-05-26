/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wait_and_pids.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/15 14:27:56 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/26 14:10:38 by bprovoos      ########   odam.nl         */
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
			g_exit_status = WEXITSTATUS (return_wait);
		else if (WIFSIGNALED (return_wait) && g_exit_status == 131)
			write(STDERR, "Quit: 3\n", 9);
		else if (WIFSIGNALED (return_wait) && g_exit_status == 130)
			write(1, "\n", 1);
	}
}
