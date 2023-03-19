/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:17:36 by edawood           #+#    #+#             */
/*   Updated: 2023/03/19 14:40:30 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	print_export(t_env *env)
{
	while (env)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		if (env->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd("", 1);
		if (!env->next)
			return ;
		env = env->next;
	}
}

void	export_util(char *key, char *value, t_env *env)
{
	if (!key)
		return ;
	if (value)
		set_env(key, value, env);
	else
		set_env(key, NULL, env);
	free(key);
	if (value)
		free(value);
}

bool	is_not_alpha_second_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_' \
			&& str[i] != '?')
			return (export_error(str));
		i++;
	}
	return (true);
}

bool	is_not_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 0 && str[i] != '_' \
			&& str[i] != '?' && str[i] != '=')
			return (export_error(str));
		i++;
	}
	return (true);
}

bool	check_if_cmd_is_word(t_cmd *cmd, int i)
{
	if (!(is_not_alpha(cmd->exec->cmd_args[i])))
		return (false);
	if (cmd->exec->cmd_args[i][0] == '=')
		return (export_error(cmd->exec->cmd_args[i]));
	return (true);
}
