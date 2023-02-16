/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:13:54 by edawood           #+#    #+#             */
/*   Updated: 2023/02/16 13:50:23 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	print_export(t_env *env)
{
	while (env->next)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(env->value, 1);
		ft_putendl_fd("\"", 1);
		env = env->next;
	}
}

void	set_env(char *key, char *value, t_env *env)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env->next)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key)) == 0)
		{
			tmp = ft_strjoin(key, "=");
			if (!tmp)
				return ;
			tmp = ft_strjoin(tmp, value);
			if (!tmp)
				return ;
			free(env->key);
			env->key = tmp;
		}
		i++;
	}
}

static void	export_util(char *key, char *value, t_env *env)
{
	if (!key)
		return ;
	if (value)
		set_env(key, value, env);
	else
		set_env(key, "", env);
	free(key);
	if (value)
		free(value);
}

int	minishell_export(char *arg, t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 1;
	if (!arg)
		return (ERROR);
	while (cmd->exec->args[i])
	{
		j = 0;
		while (cmd->exec->args[i][j] && cmd->exec->args[i][j] != '=')
			j++;
		key = ft_substr(cmd->exec->args[i], 0, j);
		if (cmd->exec->args[i][j] == '=')
			value = ft_substr(cmd->exec->args[i], j + 1, \
					ft_strlen(cmd->exec->args[i]) - j);
		else
			value = NULL;
		export_util(key, value, env);
		i++;
	}
	if (i == 1)
		print_export(env);
	return (SUCCESS);
}
