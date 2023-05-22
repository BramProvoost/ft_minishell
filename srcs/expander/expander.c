/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:03:55 by bprovoos          #+#    #+#             */
/*   Updated: 2023/05/22 18:05:46 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*ft_strjoin_exp(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[c] != '\0')
		str[i++] = s2[c++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	if (s1)
	{
		free(s1);
		s1 = NULL;
	}
	return (str);
}

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
			if (!ft_strncmp(env->key, key, ft_strlen(env->key)))
				return (ft_strdup(env->value));
		}
		env = env->next;
	}
	return (ft_strdup(""));
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
	char	*tmp;

	i = 0;
	varname = NULL;
	if (str[1] == '\0' || str[1] == ' ')
	{
		varname = (char *)malloc(sizeof(char) * 2);
		varname[0] = str[1];
		varname[1] = '\0';
		return (varname);
	}
	else if (str[1] == '?' || str[1] == '$')
	{
		varname = (char *)malloc(sizeof(char) * 3);
		varname[0] = str[0];
		varname[1] = str[1];
		varname[2] = '\0';
		return (varname);
	}
	while (is_valid_varname_char(str[i]) || i == 0)
	{
		tmp = varname;
		varname = ft_append_char_to_string(tmp, str[i]);
		i += 1;
		free(tmp);
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

	expanded = NULL;
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
	char	*tmp;
	int		i;
	char	*tmp2;
	char	*tmp3;

	newstr = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !in_single_quotes(str, i))
		{
			varname = get_varname(&str[i]);
			tmp2 = newstr;
			tmp3 = expand_variable(varname, env);
			newstr = ft_strjoin_exp(tmp2, tmp3);
			free(tmp2);
			free(tmp3);
			i += ft_strlen(varname) - 1;
			free(varname);
		}
		else
		{
			tmp = newstr;
			newstr = ft_append_char_to_string(tmp, str[i]);
			free(tmp);
		}
		i++;
	}
	return (newstr);
}

void	expander(t_token **tokens, t_env *env)
{
	t_token	*tmp;
	char	*tmp_val;

	tmp = *tokens;
	tmp_val = NULL;
	while (tmp)
	{
		if (!(tmp->prev && tmp->prev->type == HEREDOC))
		{
			tmp_val = tmp->value;
			tmp->value = expand(tmp_val, env);
			free(tmp_val);
			tmp_val = NULL;
		}
		if (tmp->type != WORD && !(tmp->prev && tmp->prev->type == HEREDOC))
			tmp->value = rm_quotes(tmp->value);
		tmp = (tmp)->next;
	}
}
