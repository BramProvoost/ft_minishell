/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_cd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/12 14:46:00 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:27:27 by bprovoos      ########   odam.nl         */
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

int	minishell_cd(char *arg, t_cmd *cmd, t_args *args)
{
	if (!arg || (arg[0] == '\0'))
		return (ERROR);
	args->home_path = get_all_paths("HOME=", args->env);
	if (!args->home_path)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), SUCCESS);
	if (!cmd->exec->args[1])
	{
		if (chdir(args->home_path) == ERROR)
			chdir_error(args->home_path, errno);
	}
	else
	{
		if (chdir(cmd->exec->args[1]) == ERROR)
			chdir_error(arg, errno);
	}
	return (SUCCESS);
}
