/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:46:00 by edawood           #+#    #+#             */
/*   Updated: 2023/03/19 17:46:03 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	write_error_with_strings(char *str1, char *str2, char *str3)
{
	write(2, str1, ft_strlen(str1));
	write(2, str2, ft_strlen(str2));
	write(2, str3, ft_strlen(str3));
}

int	chdir_error(char *str, int32_t error)
{
	if (error == EACCES)
		write_error_with_strings("minishell: cd: ", str, \
								": Permission denied\n");
	else if (error == ENOENT)
		write_error_with_strings("minishell: cd: ", str, \
								": No such file or directory\n");
	else if (error == ENOTDIR)
		write_error_with_strings("minishell: cd: ", str, \
								": Not a directory\n");
	else
		write_error_with_strings("minishell: cd: ", str, \
								": Change directory error\n");
	return (1);
}

char	*get_home_path(t_env *env)
{
	while (env->next)
	{
		if (!ft_strncmp("HOME", env->key, ft_strlen("HOME")))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	minishell_cd(t_cmd *cmd, t_env *env)
{
	char	*home_path;

	home_path = get_home_path(env);
	if (!home_path)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), SUCCESS);
	if (!cmd->exec->cmd_args[1])
	{
		if (chdir(home_path) == ERROR)
			chdir_error(home_path, errno);
	}
	else
	{
		if (chdir(cmd->exec->cmd_args[1]) == ERROR)
			chdir_error(cmd->exec->cmd_args[1], errno);
	}
	return (SUCCESS);
}
