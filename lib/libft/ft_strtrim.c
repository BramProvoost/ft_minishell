/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 22:09:54 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:32:10 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, char const *set)
{
	size_t	set_counter;

	set_counter = 0;
	while (set[set_counter])
	{
		if (c == set[set_counter])
			return (1);
		set_counter++;
	}
	return (0);
}

int	get_start_trim(char const *s1, char const *set)
{
	size_t	counter;
	size_t	start;

	counter = 0;
	start = counter;
	while (s1[counter])
	{
		if (is_in_set(s1[counter], set) && start == counter)
			start++;
		else
			return (start);
		counter++;
	}
	return (start);
}

int	get_end_trim(char const *s1, char const *set)
{
	size_t	counter;
	size_t	end;

	counter = ft_strlen(s1) - 1;
	end = counter;
	while (counter > 0)
	{
		if (is_in_set(s1[counter], set) && end == counter)
			end--;
		else
			return (end + 1);
		counter--;
	}
	return (end + 1);
}

/*
	Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters 
	specified in ’set’ removed from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	stop;

	if (!s1)
		return (ft_substr(s1, 0, 0));
	if (!set)
		return (ft_strdup(s1));
	start = get_start_trim(s1, set);
	stop = get_end_trim(s1, set);
	if (start > stop)
		return (ft_substr(s1, 0, 0));
	return (ft_substr(s1, start, stop - start));
}
