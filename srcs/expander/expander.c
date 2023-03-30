/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 10:03:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/03/30 16:08:32 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*rm_quotes(char *str)
{
	return (str);
}

char	*get_value_from_env(char *key, t_env *env)
{
	while (env)
	{
		if (env->has_value == true)
		{
			if (!ft_strncmp(env->key, key, ft_strlen(key)))
				return (env->value);
		}
		env = env->next;
	}
	return ("");
}

char	*expand(char *str, t_env *env)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	newstr = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			j = i + 1;
			while (str[j] && str[j] != ' ' && str[j] != ',' && str[j] != '.' && str[j] != '\0')
				j++;
			newstr = ft_strjoin(newstr, get_value_from_env(ft_substr(str, i + 1, j - i - 1), env));
			i = j;
			continue;
		}
		newstr = ft_strjoin(newstr, ft_strlendump(&str[i], 1));
		i++;
	}
	return (newstr);
}

void	expander(t_token **tokens, t_env *env)
{
	t_token	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		tmp->value = expand(tmp->value, env);
		tmp->value = rm_quotes(tmp->value);
		tmp = (tmp)->next;
	}
	(void)env;
}
