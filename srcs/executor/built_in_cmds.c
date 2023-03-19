/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:50:22 by edawood           #+#    #+#             */
/*   Updated: 2023/03/16 14:05:51 by edawood          ###   ########.fr       */
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

int	execute_built_in_cmd(t_cmd *cmd_list, char *cmd, t_env *env)
{
	if (!cmd)
		return (ERROR);
	if (!ft_strncmp(cmd, "echo", 5))
		return (minishell_echo(cmd_list));
	if (!ft_strncmp(cmd, "cd", 3))
		return (minishell_cd(cmd_list->exec->cmd_args[0], cmd_list, env));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (minishell_pwd());
	else if (!ft_strncmp(cmd, "export", 7))
		return (minishell_export(cmd_list, env));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (minishell_unset(cmd_list, env));
	else if (!ft_strncmp(cmd, "env", 4))
		return (minishell_env(env));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (minishell_exit(cmd_list->exec->cmd_args[0], cmd_list));
	return (ERROR);
}
