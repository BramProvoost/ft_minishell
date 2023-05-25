/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 10:03:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/25 12:51:03 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	add_varname_to_str(char **newstr, char *str, int i, t_env *env)
{
	char	*varname;
	char	*tmp2;
	char	*tmp3;

	varname = get_varname(&str[i]);
	tmp2 = *newstr;
	tmp3 = expand_variable(varname, env);
	*newstr = ft_strjoin_exp(tmp2, tmp3);
	tmp2 = NULL;
	free(tmp2);
	free(tmp3);
	if (ft_strlen(varname) > 1)
		i += ft_strlen(varname) - 1;
	free(varname);
	return (i);
}

char	*expand(char *str, t_env *env)
{
	char	*newstr;
	char	*tmp;
	int		i;

	newstr = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && !in_single_quotes(str, i))
			i = add_varname_to_str(&newstr, str, i, env);
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
