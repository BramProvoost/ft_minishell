/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/03 16:11:48 by bramjr        #+#    #+#                 */
/*   Updated: 2022/12/02 11:48:11 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **splits)
{
	int	i;

	i = 0;
	while (splits[i])
	{
		free(splits[i]);
		i++;
	}
	free(splits);
}

int	count_splits(char const *s, char c)
{
	int		i;
	int		amount;

	i = 0;
	amount = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		if (s[i - 1] != c)
			amount++;
	}
	return (amount);
}

int	start_stop(char const *s, char c, int *i, int mode)
{
	while (s[*i] && s[*i] == c && mode == 1)
		(*i)++;
	while (s[*i] && s[*i] != c && mode == 2)
		(*i)++;
	return (*i);
}

char	**splitting(char const *s, char c, char **splits, int amount)
{
	int		i;
	int		j;
	int		start;
	int		stop;

	i = 0;
	j = 0;
	while (j < amount)
	{
		start = start_stop(s, c, &i, 1);
		stop = start_stop(s, c, &i, 2);
		if (s[i - 1] != c)
			splits[j] = ft_substr(s, start, stop - start);
		if (!splits[j])
		{
			free_split(splits);
			return (0);
		}
		j++;
	}
	splits[j] = NULL;
	return (splits);
}

char	**ft_split(char const *s, char c)
{
	int		amount;
	char	**splits;

	if (!s)
		return (NULL);
	amount = (count_splits(s, c));
	splits = (char **)malloc(sizeof(char *) * (amount + 1));
	if (!splits)
		return (NULL);
	splits = splitting(s, c, splits, amount);
	return (splits);
}
