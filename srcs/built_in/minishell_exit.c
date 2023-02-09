/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/22 18:21:22 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:27:40 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_exit(char *arg, t_cmd *cmd, t_args *args)
{
	if (cmd->exec->args[1] && cmd->exec->args[2])
	{
		ft_putstr_fd("exit\n", STDERR);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR);
		return (ERROR);
	}
	if (cmd->exec->args[1])
	{
		if (ft_isdigit(cmd->exec->args[1][0]))
			args->status_code = ft_atoi(cmd->exec->args[1]);
		else
		{
			ft_putstr_fd("exit\n", STDERR);
			ft_putstr_fd("minishell: exit: ", STDERR);
			ft_putstr_fd(arg, STDERR);
			ft_putstr_fd(": numeric argument required\n", STDERR);
			return (ERROR);
		}
	}
	ft_putstr_fd("exit\n", STDERR);
	exit(args->status_code);
}
