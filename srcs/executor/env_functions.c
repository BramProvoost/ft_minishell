/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_functions.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 18:57:18 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/27 14:45:25 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	set_env_node(t_env *new, char *env, int len)
{
	int	i;

	i = 0;
	while (env[i] && new->has_value == false)
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
}

t_env	*new_env_node(char *env)
{
	t_env	*new;
	int		len;

	len = ft_strlen(env);
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->has_value = false;
	new->next = NULL;
	set_env_node(new, env, len);
	return (new);
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

char	**env_to_list(t_env *env)
{
	char	**env_list;
	int		i;
	char	*tmp;

	i = 0;
	env_list = (char **)malloc(sizeof(char *) * (get_env_len(env) + 1));
	if (!env_list)
		return (errno = ENOMEM, NULL);
	while (env)
	{
		if (!env->key || !env->value)
			return (errno = EINVAL, NULL);
		tmp = ft_strjoin(env->key, "=");
		if (!tmp)
			return (errno = EINVAL, NULL);
		env_list[i] = ft_strjoin(tmp, env->value);
		if (!env_list[i])
			return (errno = EINVAL, NULL);
		free(tmp);
		env = env->next;
		i++;
	}
	env_list[i] = NULL;
	return (env_list);
}
