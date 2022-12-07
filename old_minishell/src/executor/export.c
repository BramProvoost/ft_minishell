/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 20:08:09 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/10/27 14:14:28 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**append_env(char **envp, char *variable)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	
	if (!envp)
		return(NULL);
	while(envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 2);
	if (!new_envp)
		return (NULL);
	j = 0;
	while(j < i)
	{
		new_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	new_envp[j] = ft_strdup(variable);
	return (new_envp);
}

char	**change_env(char **envp, char *variable, char *change)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	
	if (!envp)
		return(NULL);
	while(envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i + 1);
	if (!new_envp)
		return (NULL);
	j = 0;
	while(j < i)
	{
		if (ft_strcmp(new_envp[j], variable) == 0)
			new_envp[j] = ft_strdup(change);
		else
			new_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	return (new_envp);
}

char	**remove_env(char **envp, char *variable)
{
	int		i;
	int		j;
	int		k;
	char	**new_envp;

	i = 0;
	
	if (!envp)
		return(NULL);
	while(envp[i])
		i++;
	new_envp = malloc(sizeof(char *) * i);
	if (!new_envp)
		return (NULL);
	j = 0;
	k = 0;
	while(j < i)
	{
		if (ft_strcmp(new_envp[k], variable) == 0)
		{
			new_envp[j] = ft_strdup(variable);
			k++;
		}
		else
			new_envp[j] = ft_strdup(envp[k]);
		k++;
	}
	return (new_envp);
}