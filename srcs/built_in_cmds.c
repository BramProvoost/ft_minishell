/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cmd_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:28:28 by edawood           #+#    #+#             */
/*   Updated: 2022/12/15 10:29:42 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

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
