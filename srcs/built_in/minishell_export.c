/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_export.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/22 16:13:54 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:27:43 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	print_export(t_args *args)
{
	while (args->env->next)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(args->env->key, 1);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(args->env->value, 1);
		ft_putendl_fd("\"", 1);
		args->env = args->env->next;
	}
}

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
	if (i == 1)
		print_export(args);
	return (SUCCESS);
}
