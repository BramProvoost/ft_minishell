/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:03:55 by bprovoos          #+#    #+#             */
/*   Updated: 2023/05/21 14:29:51 by edawood          ###   ########.fr       */
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
			if (!ft_strncmp(env->key, key, ft_strlen(env->key)))				
				return (ft_strdup(env->value));
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
	char	*tmp;

	i = 0;
	varname = NULL;
	if (str[1] == '\0' || str[1] == ' ' || str[1] == '?' || str[1] == '$')
	{
		varname = (char *)malloc(sizeof(char) * 2);
		varname[0] = str[1];
		varname[1] = '\0';
		return (varname);
	}
	while (is_valid_varname_char(str[i]) || i == 0)
	{
		tmp = varname;
		varname = ft_append_char_to_string(tmp, str[i]);
		free(tmp);
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
	char	*tmp;
	int		i;
	char	*tmp2;

	newstr = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !in_single_quotes(str, i))
		{
			varname = get_varname(&str[i]);
			tmp2 = newstr;
			// fprintf(stderr, "%s\n", tmp2);
			// newstr = ft_strdup("");
			newstr = ft_strjoin(tmp2, expand_variable(varname, env));
			free(tmp2);
			i += ft_strlen(varname) - 1;
			free(varname);
			fprintf(stderr, "newstr: %s\n", newstr);
			// free(newstr);
			// free(str);
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
	char	*tmp2;

	tmp = *tokens;
	tmp_val = NULL;
	tmp2 = NULL;
	while (tmp)
	{
		if (!(tmp->prev && tmp->prev->type == HEREDOC))
		{
			tmp_val = tmp->value;
			tmp->value = expand(tmp_val, env);
			// fprintf(stderr, "tmp->value: %s\n", tmp->value);
			free(tmp_val);
		}
		if (tmp->type != WORD && !(tmp->prev && tmp->prev->type == HEREDOC))
		{
			tmp2 = tmp->value;
			tmp->value = rm_quotes(tmp2);
			free(tmp2);
		}
		tmp = (tmp)->next;
	}
}
