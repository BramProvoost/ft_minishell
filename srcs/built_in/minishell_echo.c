/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:22:53 by edawood           #+#    #+#             */
/*   Updated: 2023/03/09 18:24:25 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static bool	check_n_flag(t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	if (cmd->exec->cmd_args[i][j] == '-')
	{
		j++;
		while (cmd->exec->cmd_args[i][j] == 'n')
			j++;
		return (true);
	}
	return (false);
}

int	minishell_echo(t_cmd *cmd)
{
	int		i;

	i = 1;
	cmd->echo_n_flag = false;
	cmd->echo_print_flag = false;
	while (cmd->exec->cmd_args[i])
	{
		if (check_n_flag(cmd, i) == true)
		{
			cmd->echo_n_flag = true;
			cmd->echo_print_flag = true;
		}
		if (cmd->echo_print_flag == true)
		{
			cmd->echo_print_flag = false;
			i++;
		}
		ft_putstr_fd(cmd->exec->cmd_args[i], 1);
		if (cmd->exec->cmd_args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (cmd->echo_n_flag == false)
		ft_putendl_fd("", 1);
	return (SUCCESS);
}
