/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:57:18 by edawood           #+#    #+#             */
/*   Updated: 2023/01/29 19:48:46 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

t_env	*new_env_node(char *env)
{
	t_env	*new;
	int		i;
	int		len;

	i = 0;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	while (env[i])
	{
		len = ft_strlen(env);
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
		new->value = ft_strdup("");
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
