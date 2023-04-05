/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 10:03:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/04/05 20:59:25 by bprovoos      ########   odam.nl         */
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

//
char *expand_special_cases(char *str) {
	if (str[1] == '$') {
		return "$";
	} else if (str[1] == '?') {
		return ft_itoa(g_exit_status);
	}
	return "";
}

bool in_quotes(char *str, int index) {
	int quote_count = 0;
	for (int i = 0; i < index; i++) {
		if (str[i] == '\'') {
			quote_count++;
		}
	}
	return (quote_count % 2 != 0);
}

bool is_valid_env_char(char c) {
	return (ft_isalnum(c) || c == '_');
}

char *expand_variable(char *str, t_env *env)
{
	char *expanded_str = NULL;
	int i = 0;
	// printf("str: %s\n", str);
	while (str[i])
	{
		if (str[i] == '$')
		{
			int j = i + 1;
			while (str[j] && str[j] != ' ' && str[j] != ',' && str[j] != '.'  && str[j] != '\'' && str[j] != '"' && str[j] != '$' && str[j] != '\0')
				j++;
			// printf("input: %s\n", ft_substr(str, i + 1, j - i - 1));
			expanded_str = ft_strjoin(expanded_str, get_value_from_env(ft_substr(str, i + 1, j - i - 1), env));
			// printf("output: %s\n", get_value_from_env(ft_substr(str, i + 1, j - i - 1), env));
			i = j - 1;
			continue;
		}
		expanded_str = ft_strjoin(expanded_str, ft_strlendump(&str[i], 1));
		i++;
	}
	return expanded_str;
}

// char *expand(char *str, t_env *env) {
// 	char *newstr = ft_strdup("");
// 	int i = 0;
// 	while (str[i]) {
// 		bool do_expand = !in_quotes(str, i);
// 		if (str[i] == '$' && do_expand) {
// 			newstr = ft_strjoin(newstr, expand_special_cases(&str[i]));
// 			i += 2;
// 		} else {
// 			newstr = ft_strjoin(newstr, ft_strlendump(&str[i], 1));
// 			i++;
// 		}
// 	}
// 	char *expanded_str = expand_variable(newstr, env);
// 	free(newstr);
// 	return expanded_str;
// }

bool is_valid_varname_char(char c) {
	if (ft_isalpha(c) || c == '_')
		return true;
	if (ft_isdigit(c))
		return true;
	return false;
}

char *get_varname(char *str, int *i) {
	char *varname = NULL;
	int len = 0;
	*i += 1;
	while (is_valid_varname_char(str[*i])) {
		varname = realloc(varname, len + 1);
		varname[len++] = str[*i];
		*i += 1;
	}
	varname = realloc(varname, len + 1);
	varname[len] = '\0';
	return varname;
}

// char *get_varname(char *str, int *i) {
// 	char *varname = NULL;
// 	int j = 0;
// 	(*i)++; // skip the '$' character
// 	while (str[*i] && is_valid_varname_char(str[*i])) {
// 		j++;
// 		(*i)++;
// 	}
// 	if (j > 0) {
// 		varname = ft_strdup(&str[*i - j]);
// 	}
// 	return varname;
// }

char *expand(char *str, t_env *env) {
	char *newstr = NULL;
	int i = 0;
	while (str[i]) {
		bool do_expand = !in_quotes(str, i);
		if (str[i] == '$' && do_expand) {
			char *expanded = NULL;
			if (str[i + 1] == '$' || str[i + 1] == '?') {
				expanded = expand_special_cases(&str[i]);
				i += 2;
			} else {
				char *varname = get_varname(str, &i);
				expanded = expand_variable(varname, env);
				free(varname);
				i += ft_strlen(varname) + 1;
			}
			newstr = ft_strjoin(newstr, expanded);
			free(expanded);
		} else {
			newstr = ft_strjoin(newstr, ft_strlendump(&str[i], 1));
			i++;
		}
	}
	char *expanded_str = expand_variable(newstr, env);
	free(newstr);
	return expanded_str;
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
