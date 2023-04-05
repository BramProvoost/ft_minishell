/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 10:03:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/04/05 17:50:13 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*rm_quotes(char *str)
{
	char	quote;
	int		i;

	i = 0;
	quote = '0';
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (quote == str[i])
				quote = '0';
			else if (quote == '0')
				quote = str[i];
			if (quote == '0' || quote == str[i])
				ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i]));
		}
		i++;
	}
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
	bool	do_expand;

	i = 0;
	newstr = NULL;
	do_expand = true;
	while (str[i])
	{
		if (str[i] == '\'')	// not working in double quotes!
			do_expand = !do_expand;
		if (str[i] == '$' && do_expand)
		{
			j = i + 1;
			while (str[j] && str[j] != ' ' && str[j] != ',' && str[j] != '.'  && str[j] != '\'' && str[j] != '"' && str[j] != '$' && str[j] != '\0')
				j++;
			newstr = ft_strjoin(newstr, get_value_from_env(ft_substr(str, i + 1, j - i - 1), env));
			i = j;
			continue;
		}
		newstr = ft_strjoin(newstr, ft_strlendump(&str[i], 1));
		i++;
	}
	free(str);
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
}
