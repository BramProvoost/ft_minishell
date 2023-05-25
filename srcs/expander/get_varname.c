/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_varname.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/25 12:13:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/25 13:06:15 by bprovoos      ########   odam.nl         */
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

int	is_valid_varname_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (1);
	if (ft_isdigit(c))
		return (1);
	return (0);
}

char	*custom_malloc(const char *str)
{
	char	*varname;

	if (str[1] == '\0')
	{
		varname = (char *)malloc(sizeof(char) * 1);
		varname[0] = str[1];
		return (varname);
	}
	else if (str[1] == ' ')
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
	return (NULL);
}

char	*get_varname(char *str)
{
	int		i;
	char	*varname;
	char	*tmp;

	i = 0;
	varname = NULL;
	if (str[1] == '\0' || str[1] == ' ' || str[1] == '?' || str[1] == '$')
		return (custom_malloc(str));
	while (is_valid_varname_char(str[i]) || i == 0)
	{
		tmp = varname;
		varname = ft_append_char_to_string(tmp, str[i]);
		i += 1;
		free(tmp);
	}
	return (varname);
}
