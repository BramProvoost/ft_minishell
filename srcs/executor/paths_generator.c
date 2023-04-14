/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   paths_generator.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 16:48:44 by edawood       #+#    #+#                 */
/*   Updated: 2023/04/14 15:13:48 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_2d(char **paths)
{
	int	i;

	i = 0;
	while (paths && paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	**ft_strdup2d(char **str)
{
	char	**newstr;
	int		i;

	i = 0;
	while (str[i])
		i++;
	newstr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!newstr)
		return (NULL);
	i = 0;
	while (str[i])
	{
		newstr[i] = ft_strdup(str[i]);
		i++;
	}
	newstr[i] = NULL;
	return (newstr);
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
