/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/19 13:17:36 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/27 14:45:11 by bprovoos      ########   odam.nl         */
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

void	export_util(char *key, char *value, t_env **env)
{
	char	*tmp2;

	tmp2 = NULL;
	if (!key)
		return ;
	if (!*env)
	{
		tmp2 = assign_tmps(&tmp2, key, value);

		*env = new_env_node(tmp2);
		if (value)
			free(tmp2);
		return ;
	}
	if (value)
		set_env(key, value, *env);
	else
		set_env(key, NULL, *env);
	free(key);
	if (value)
		free(value);
}

bool	value_in_quotes(char *str, int i)
{
	while (str[i])
	{
		if (str[i] == '"')
			return (true);
		i++;
	}
	export_error(str);
	return (false);
}

bool	is_not_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0)
		{
			if (ft_isalpha(str[i]) == 0 && str[i] != '_' \
				&& str[i] != '?' && str[i] != '=')
				return (export_error(str));
		}
		if (str[i] == '=' && str[i + 1] == '"')
			return (value_in_quotes(str, i + 2));
		if ((ft_isalnum(str[i]) == 0) && str[i] != '_' \
			&& str[i] != '?' && str[i] != '=')
			return (export_error(str));
		i++;
	}
	return (true);
}

bool	check_if_cmd_is_word(t_cmd *cmd, int i)
{
	char	*tmp;

	if (!(is_not_alpha(cmd->exec->cmd_args[i])))
		return (false);
	tmp = rm_quotes(cmd->exec->cmd_args[i]);
	if (tmp)
		cmd->exec->cmd_args[i] = tmp;
	if (cmd->exec->cmd_args[i][0] == '=')
		return (export_error(cmd->exec->cmd_args[i]));
	return (true);
}
