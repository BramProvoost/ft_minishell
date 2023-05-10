/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 10:03:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/10 14:30:31 by bprovoos      ########   odam.nl         */
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
			{
				ft_memmove(&str[i], &str[i + 1], ft_strlen(&str[i]));
				i--;
			}
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
			if (!ft_strncmp(env->key, key, ft_strlen(key))) // TODO: USER != USER_ZDOTDIR
				return (env->value);
		}
		env = env->next;
	}
	return ("");
}

int	is_valid_varname_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return true;
	if (ft_isdigit(c))
		return true;
	return false;
}

char	*get_varname(char *str)
{
	int		i;
	char	*varname;

	i = 0;
	varname = NULL;
	if (str[1] == '\0' || str[1] == ' ')
		return (ft_strlendump(str, 1));
	if (str[1] == '?' || str[1] == '$')
		return (ft_strlendump(str, 2));
	while (is_valid_varname_char(str[i]) || i == 0)
	{
		varname = ft_strjoin(varname, ft_strlendump(&str[i], 1));
		i += 1;
	}
	return (varname);
}

char	*expand_special_cases(char *str)
{
	if (str[1] == '?')
		return ft_itoa(g_exit_status);
	return ft_strdup("$");
}

char	*expand_variable(char *varname, t_env *env)
{
	char	*expanded;

	if (varname[1] && (varname[1] == '?'))
		expanded = expand_special_cases(varname);
	else if (!varname[1] || varname[1] == ' ')
		expanded = ft_strdup("$");
	else
		expanded = get_value_from_env(&varname[1], env);
	return (expanded);
}

int	in_single_quotes(char *str, int index)
{
	int	i;
	int	is_in_quotes;

	i = 0;
	is_in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '\'' && i < index)
			is_in_quotes = !is_in_quotes;
		i++;
	}
	return (is_in_quotes);
}

char	*expand(char *str, t_env *env)
{
	char 	*newstr;
	char	*varname;
	int		i;

	newstr = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !in_single_quotes(str, i))
		{
			varname = get_varname(&str[i]);
			newstr = ft_strjoin(newstr, expand_variable(varname, env));
			i += ft_strlen(varname) - 1;
			free(varname);
		}
		else
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
		if (tmp->type != WORD && !(tmp->prev && tmp->prev->type == HEREDOC))
			tmp->value = rm_quotes(tmp->value);
		tmp = (tmp)->next;
	}
}
