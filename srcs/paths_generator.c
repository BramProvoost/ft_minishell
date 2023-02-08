/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:48:44 by edawood           #+#    #+#             */
/*   Updated: 2022/12/11 15:04:52 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

char    *get_all_paths(char **env)
{
    while (*env != '\0')
	{		
		if (!ft_strncmp("PATH=", *env, 5))
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char    *init_paths(char **cmd, char **env)
{
	char	**paths;
	char	*path;
	char	*temp_path;
    int     i;

    i = 0;
	temp_path = get_all_paths(env);
    if (!temp_path)
        paths = ft_split("", ':');
    else
        paths = ft_split(temp_path, ':');
    if (!paths)
    {
        errno = ENOMEM;
        return (NULL);
    }
	if (access(*cmd, X_OK) == 0)
		return (*cmd);
    while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp_path, cmd[0]);
		free(temp_path);
		if (access(paths[i], X_OK) == 0)
			return (path);
		free(path);
		free(paths[i++]);
	}
	free(paths);
	return (NULL);
}
