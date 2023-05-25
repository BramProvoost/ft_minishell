/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:13:54 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 11:33:57 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

bool	check_if_env_key_exists(t_env *env, char *key, char *value)
{
	if (!(ft_strncmp(env->key, key, ft_strlen(key))))
	{
		if (value)
		{
			free(env->value);
			env->value = ft_strdup(value);
			env->has_value = true;
		}
		else
		{
			free(env->value);
			env->value = NULL;
			env->has_value = false;
		}
		return (true);
	}
	return (false);
}

char	*assign_tmps(char **tmp, char **tmp2, char *key, char *value)
{
	if (value)
	{
		*tmp = ft_strjoin(key, "=");
		*tmp2 = ft_strjoin(*tmp, value);
		free(*tmp);
	}
	else
		tmp2 = &key;
	return (*tmp2);
}

void	set_env(char *key, char *value, t_env *env)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = assign_tmps(&tmp, &tmp2, key, value);
	while (env)
	{
		if (check_if_env_key_exists(env, key, value))
		{
			if (value)
				free(tmp2);
			return ;
		}
		if (!env->next)
		{
			env->next = new_env_node(tmp2);
			if (value)
				free(tmp2);
			return ;
		}
		else
			env = env->next;
	}
}

char	*get_export_value(t_cmd *cmd, int i, int j)
{
	if (cmd->exec->cmd_args[i][j] == '=')
	{
		if (cmd->exec->cmd_args[i][j + 1] == '\0')
			return (ft_strdup(""));
		else
			return (ft_substr(cmd->exec->cmd_args[i], j + 1, \
					ft_strlen(cmd->exec->cmd_args[i]) - j));
	}
	else
		return (NULL);
}

int	minishell_export(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 1;
	while (cmd->exec->cmd_args[i])
	{
		j = 0;
		if (!check_if_cmd_is_word(cmd, i))
		{
			i++;
			continue ;
		}
		while (cmd->exec->cmd_args[i][j] && cmd->exec->cmd_args[i][j] != '=')
			j++;
		key = ft_substr(cmd->exec->cmd_args[i], 0, j);
		value = get_export_value(cmd, i, j);
		export_util(key, value, env);
		i++;
	}
	if (cmd->exec->cmd_args[1] == NULL)
		print_export(env);
	return (SUCCESS);
}
