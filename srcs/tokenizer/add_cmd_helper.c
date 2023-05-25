/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_cmd_helper.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 16:40:02 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/19 17:05:28 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_cmd	*new_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (cmd);
}

void	add_t_cmd_back(t_cmd *cmd)
{
	if (!cmd)
	{
		cmd = new_t_cmd();
	}
	else
	{
		while ((cmd)->next)
			cmd = (cmd)->next;
		(cmd)->next = new_t_cmd();
	}
}

t_exec	*new_t_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (exec);
}

t_file	*new_t_file(void)
{
	t_file	*type;

	type = ft_calloc(1, sizeof(t_file));
	if (!type)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (type);
}

void	rm_quotes_from_2d_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		array[i] = rm_quotes(array[i]);
		i++;
	}
}
