/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_in_cmds.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 19:50:22 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:30:40 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	is_built_in_cmd(t_cmd *cmd_list, char *cmd, t_args *args)
{
	if (!cmd)
		return (ERROR);
	if (!ft_strncmp(cmd, "echo", 5))
		return (minishell_echo(cmd_list->arg, cmd_list));
	if (!ft_strncmp(cmd, "cd", 3))
		return (minishell_cd(cmd_list->arg, cmd_list, args));
	else if (!ft_strncmp(cmd, "pwd", 4))
		return (minishell_pwd());
	else if (!ft_strncmp(cmd, "export", 7))
		return (minishell_export(cmd_list->arg, cmd_list, args));
	else if (!ft_strncmp(cmd, "unset", 6))
		return (minishell_unset(cmd_list, args));
	else if (!ft_strncmp(cmd, "env", 4))
		return (minishell_env(args->env));
	else if (!ft_strncmp(cmd, "exit", 5))
		return (minishell_exit(cmd_list->arg, cmd_list, args));
	return (ERROR);
}