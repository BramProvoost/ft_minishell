/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 19:50:22 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/27 16:53:19 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	is_buld_in_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strncmp(cmd, "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd, "export", 7))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd, "env", 4))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

int	execute_built_in_cmd(t_exec_data *exec_data, char *cmd, \
	bool exit_flag, t_env **env)
{
	g_exit_status = 0;
	if (!cmd)
		return (ERROR);
	if (!ft_strncmp(cmd, "echo", 5))
		return (minishell_echo(exec_data->cmd));
	if (!ft_strncmp(cmd, "cd", 3))
		return (minishell_cd(exec_data->cmd, exec_data->env));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (minishell_pwd());
	else if (!ft_strncmp(cmd, "export", 7))
		return (minishell_export(exec_data->cmd, env));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (minishell_unset(exec_data->cmd, env));
	else if (!ft_strncmp(cmd, "env", 4))
		return (minishell_env(exec_data->cmd, exec_data->env));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (minishell_exit(exit_flag, exec_data));
	return (ERROR);
}
