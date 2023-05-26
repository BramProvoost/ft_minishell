/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 16:24:14 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 19:37:21 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_env(t_cmd *cmd, t_env *env)
{
	if (cmd->exec->cmd_args[1])
	{
		ft_putendl_fd("env: too many arguments", 1);
		return (SUCCESS);
	}
	while (env)
	{
		if (env->has_value == true)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
		}
		if (!env->next)
			return (SUCCESS);
		env = env->next;
	}
	return (SUCCESS);
}
