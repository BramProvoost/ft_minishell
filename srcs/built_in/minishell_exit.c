/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/22 18:21:22 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/18 21:15:51 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_exit(bool print, t_exec_data *exec_data)
{
	if (exec_data->cmd->exec->cmd_args[1] && exec_data->cmd->exec->cmd_args[2] \
		&& ft_isdigit(exec_data->cmd->exec->cmd_args[1][0]))
	{
		if (print)
			ft_putstr_fd("exit\n", STDERR);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
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
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(exec_data->cmd->exec->cmd_args[1], STDERR);
			ft_putstr_fd(": numeric argument required\n", STDERR);
			exit(255);
		}
	}
	if (print)
		ft_putstr_fd("exit\n", STDERR);
	delete_cmds(exec_data->cmd);
	free_env_list(&exec_data->env);
	delete_tokens(exec_data->tokens);
	// free(exec_data); // attempting free on address which was not malloc()-ed
	exit(g_exit_status);
}
