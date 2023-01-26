/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:13:54 by edawood           #+#    #+#             */
/*   Updated: 2023/01/26 19:35:24 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

void	set_env(char *key, char *value, t_args *args)
{
	char	*tmp;
	int		i;

	i = 0;
	while (args->env->next)
	{
		if (ft_strncmp(args->env->key, key, ft_strlen(key)) == 0)
		{
			tmp = ft_strjoin(key, "=");
			if (!tmp)
				return ;
			tmp = ft_strjoin(tmp, value);
			if (!tmp)
				return ;
			free(args->env->key);
			args->env->key = tmp;
		}
		i++;
	}
}

static void	export_util(char *key, char *value, t_args *args)
{
	if (!key)
		return ;
	if (value)
		set_env(key, value, args);
	else
		set_env(key, "", args);
	free(key);
	if (value)
		free(value);
}

int	minishell_export(char *arg, t_cmd *cmd, t_args *args)
{
	int		i;
	int		j;
	char	*key;
	char	*value;
	static int test = 0;

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
		export_util(key, value, args);
		i++;
	}
	if (test == 1)
		return (SUCCESS);
	test++;
	return (SUCCESS);
}
