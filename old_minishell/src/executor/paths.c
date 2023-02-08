/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 19:56:13 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/28 15:02:00 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_env_paths(char **envp)
{
	char	*paths;

	while (*envp && ft_strncmp("PATH", *envp, 4))
		envp++;
	if (!*envp)
		exit(127);
	paths = ft_strjoin(*envp + ft_strlen("PATH="), "/");
	if (!paths)
		exit(1);
	return (paths);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**splitted_cmd;
	char	**path;
	char	*paths;
	char	*tmp;
	char	*path_and_cmd;

	splitted_cmd = ft_split(cmd, ' ');
	paths = get_env_paths(envp);
	path = ft_split(paths, ':');
	free(paths);
	if (!path)
		exit(1);
	if (access(splitted_cmd[0], X_OK) == 0)
		return (splitted_cmd[0]);
	while (*path)
	{
		tmp = ft_strjoin(*path, "/");
		path_and_cmd = ft_strjoin(tmp, splitted_cmd[0]);
		if (!tmp || !path_and_cmd)
			exit(1);
		free(tmp);
		if (access(path_and_cmd, X_OK) == 0)
			return (path_and_cmd);
		free(path_and_cmd);
		path++;
	}
	return (NULL);
}