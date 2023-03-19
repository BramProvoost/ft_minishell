/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:57:18 by edawood           #+#    #+#             */
/*   Updated: 2023/03/19 18:01:24 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_env	*new_env_node(char *env)
{
	t_env	*new;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(env);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->next = NULL;
	while (env[i])
	{
		if (env[i] == '=')
		{
			new->key = ft_substr(env, 0, i);
			new->value = ft_substr(env, i + 1, len - i);
			new->has_value = true;
		}
		i++;
	}
	if (new->has_value == false)
	{
		new->key = ft_substr(env, 0, len);
		new->value = NULL;
	}
	return (new);
}

void	free_env_list(t_env **head)
{
	t_env	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
}

bool	create_env_list(t_env **head, char **envp)
{
	int		i;
	t_env	*tmp;
	t_env	*new;

	i = 0;
	while (envp[i])
	{
		new = new_env_node(envp[i]);
		if (!new)
			return (free_env_list(head), false);
		if (i == 0)
		{
			tmp = new;
			*head = tmp;
			i++;
			continue ;
		}
		else
			tmp->next = new;
		tmp = tmp->next;
		i++;
	}
	return (true);
}

int	get_env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**env_to_list(t_env *env)
{
	char	**env_list;
	int		i;
	int		env_len;

	i = 0;
	env_len = get_env_len(env);
	env_list = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (!env_list)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (env)
	{
		if (!env->key || !env->value)
			return (errno = EINVAL, NULL);
		env_list[i] = ft_strjoin(env->key, "=");
		env_list[i] = ft_strjoin(env_list[i], env->value);
		env = env->next;
		i++;
	}
	env_list[i] = NULL;
	return (env_list);
}
