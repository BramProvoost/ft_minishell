/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:48:44 by edawood           #+#    #+#             */
/*   Updated: 2023/03/19 17:00:27 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_2d(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	return ;
}

char	*get_all_paths(char *path, t_env *env)
{
	while (env->next)
	{
		if (!ft_strncmp(path, env->key, ft_strlen(path)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
