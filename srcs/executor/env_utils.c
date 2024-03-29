/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:20:44 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 11:49:08 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	assign_env_value(t_env *new, char *env, int i, int len)
{
	new->key = ft_substr(env, 0, i);
	new->value = ft_substr(env, i + 1, len - i);
	new->has_value = true;
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
