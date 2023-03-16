/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths_generator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:48:44 by edawood       #+#    #+#                 */
/*   Updated: 2023/03/10 14:09:54 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_2d(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return ;
}

char	*get_all_paths(char *path, t_env *env)
{
	while (env->next)
	{
		if (!ft_strncmp(path, env->key, 5))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
