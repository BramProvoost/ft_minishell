/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:46:00 by edawood           #+#    #+#             */
/*   Updated: 2023/05/22 18:35:14 by edawood          ###   ########.fr       */
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
	{
		write_error_with_strings("minishell: cd: ", str, \
								": No such file or directory\n");
		g_exit_status = 1;
	}
	else if (error == ENOTDIR)
	{
		write_error_with_strings("minishell: cd: ", str, \
								": Not a directory\n");
		g_exit_status = 1;
	}
	else
		write_error_with_strings("minishell: cd: ", str, \
								": Change directory error\n");
	return (1);
}

char	*get_path(t_env *env, char *path)
{
	while (env->next)
	{
		if (!ft_strncmp(path, env->key, ft_strlen(path)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	minishell_cd(t_cmd *cmd, t_env *env)
{
	char	*home_path;
	char	*pwd;
	char	*newpwd;

	home_path = get_path(env, "HOME");
	if (!home_path)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), SUCCESS);
	pwd = get_path(env, "PWD");
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
	set_env("OLDPWD", pwd, env);
	newpwd = getcwd(NULL, 0);
	fprintf(stderr, "newpwd: %p\n", newpwd);
	set_env("PWD", newpwd, env);
	free(newpwd);
	return (SUCCESS);
}
