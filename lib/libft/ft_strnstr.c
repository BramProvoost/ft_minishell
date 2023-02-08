/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 14:56:59 by bramjr        #+#    #+#                 */
/*   Updated: 2022/09/20 17:55:20 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *source, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!to_find[0] || !n)
		return ((char *)source);
	while (source[i])
	{
		j = 0;
		while (to_find[j] == source[i + j])
		{
			if (!to_find[j + 1] && i + j < n)
				return ((char *)source + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
