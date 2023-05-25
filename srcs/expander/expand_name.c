/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_name.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:34:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/25 13:26:56 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*get_value_from_env(char *key, t_env *env)
{
	while (env)
	{
		if (env->has_value == true)
		{
			if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
				return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*expand_special_cases(char *str)
{
	if (str[1] == '?')
		return (ft_itoa(g_exit_status));
	return (ft_strdup("$"));
}

char	*expand_variable(char *varname, t_env *env)
{
	char	*expanded;

	expanded = NULL;
	if (varname[0] == '\0')
		return (ft_strdup("$"));
	if (varname[1] && (varname[1] == '?'))
	{
		expanded = expand_special_cases(varname);
		g_exit_status = 0;
	}
	else if (!varname[1] || varname[1] == ' ')
		expanded = ft_strdup("$");
	else
		expanded = get_value_from_env(&varname[1], env);
	return (expanded);
}
