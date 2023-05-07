/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 18:21:22 by edawood           #+#    #+#             */
/*   Updated: 2023/05/07 20:25:35 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_exit(char *arg, t_exec_data *exec_data)
{
	if (exec_data->cmd->exec->cmd_args[1] && exec_data->cmd->exec->cmd_args[2] \
		&& ft_isdigit(exec_data->cmd->exec->cmd_args[1][0]))
	{
		ft_putstr_fd("exit\n", STDERR);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (ERROR);
	}
	if (exec_data->cmd->exec->cmd_args[1])
	{
		if (ft_isdigit(exec_data->cmd->exec->cmd_args[1][0]))
			g_exit_status = ft_atoi(exec_data->cmd->exec->cmd_args[1]);
		else
		{
			ft_putstr_fd("exit\n", STDERR);
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(arg, STDERR);
			ft_putstr_fd(": numeric argument required\n", STDERR);
			exit(255);
		}
	}
	if (exec_data->is_pipe)
		exit(g_exit_status);
	ft_putstr_fd("exit\n", STDERR);
	exit(g_exit_status);
}
