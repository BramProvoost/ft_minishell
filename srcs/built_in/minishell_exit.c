/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/22 18:21:22 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/26 14:09:26 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	in_error_exit(t_exec_data *exec_data)
{
	ft_putstr_fd("minishell: exit: ", STDERR);
	ft_putstr_fd(exec_data->cmd->exec->cmd_args[1], STDERR);
	ft_putstr_fd(": numeric argument required\n", STDERR);
	exit(255);
}

static void	delete_befoce_exit(t_exec_data *exec_data)
{
	delete_cmds(exec_data->cmd);
	free_env_list(&exec_data->env);
	delete_tokens(exec_data->tokens);
}

int	minishell_exit(bool print, t_exec_data *exec_data)
{
	if (exec_data->cmd->exec->cmd_args[1] && exec_data->cmd->exec->cmd_args[2] \
		&& ft_isdigit(exec_data->cmd->exec->cmd_args[1][0]))
	{
		if (print)
			ft_putstr_fd("exit\n", STDERR);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		g_exit_status = 1;
		return (SUCCESS);
	}
	if (exec_data->cmd->exec->cmd_args[1])
	{
		if (ft_isdigit(exec_data->cmd->exec->cmd_args[1][0]))
			g_exit_status = ft_atoi(exec_data->cmd->exec->cmd_args[1]);
		else
		{
			if (print)
				ft_putstr_fd("exit\n", STDERR);
			in_error_exit(exec_data);
		}
	}
	if (print)
		ft_putstr_fd("exit\n", STDERR);
	delete_befoce_exit(exec_data);
	exit(g_exit_status);
}
