/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:48:44 by edawood           #+#    #+#             */
/*   Updated: 2023/01/25 20:19:08 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void	free_2d(char **paths)
{
	while (*paths)
	{
		free(*paths);
		paths++;
	}
	return ;
}

char    *get_all_paths(char *path, t_env *env)
{
    while (env->next)
	{
		if (!ft_strncmp(path, env->key, 5))
			return (env->key + 5);
		env = env->next;
	}
	return (NULL);
}

char    **init_paths(t_args *args)
{
	char	**paths;
	char	*temp_path;
    int     i;

    i = 0;
	temp_path = get_all_paths("PATH=", args->env);
    if (!temp_path)
        paths = ft_split("", ':');
    else
        paths = ft_split(temp_path, ':');
    if (!paths)
    {
        errno = ENOMEM;
        return (NULL);
    }
    while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		if (!temp_path)
		{
        	errno = ENOMEM;
        	return (NULL);
    	}
		free(paths[i]);
		paths[i] = temp_path;
		i++;
	}
	return (paths);
}
