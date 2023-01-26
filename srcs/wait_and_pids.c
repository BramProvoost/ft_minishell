/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_and_pids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:27:56 by edawood           #+#    #+#             */
/*   Updated: 2023/01/22 15:32:46 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

t_child_pids	*get_first_pid_node(void)
{
	static t_child_pids	first;

	return (&first);
}

t_child_pids	*get_last_pid_node(void)
{
	t_child_pids	*tmp;

	tmp = get_first_pid_node();
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	save_pid(pid_t new_pid)
{
	t_child_pids	*new;
	t_child_pids	*last;

	new = malloc(sizeof(t_child_pids));
	if (!new)
		return (ERROR);
	new->pid = new_pid;
	new->next = NULL;
	last = get_last_pid_node();
	last->next = new;
	return (SUCCESS);
}

void	reset_pid(void)
{
	t_child_pids	*tmp;
	t_child_pids	*next;

	tmp = get_first_pid_node();
	tmp = tmp->next;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	tmp = get_first_pid_node();
	tmp->next = NULL;
}

void	wait_for_pids(t_args *args)
{
	t_child_pids	*node;
	t_child_pids	*last_child;
	int				return_wait;

	node = get_first_pid_node();
	last_child = get_last_pid_node();
	if (!node->next)
		return ;
	waitpid(last_child->pid, &return_wait, 0);
	while (node && node->next)
	{
		wait(NULL);
		node = node->next;
	}
	reset_pid();
	if (!WIFSIGNALED (return_wait))
		args->status_code = WEXITSTATUS (return_wait);
	else if (WIFSIGNALED (return_wait) && args->status_code == 131)
		write(STDERR, "Quit: 3\n", 9);
	else if (WIFSIGNALED (return_wait) && args->status_code == 130)
		write(1, "\n", 1);
}