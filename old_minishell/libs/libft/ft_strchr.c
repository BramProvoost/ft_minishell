/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 12:20:24 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/10/28 08:19:14 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *str, int c)
{
	int	needle;

	needle = 0;
	while (str[needle])
	{
		if (str[needle] == c)
			return ((char *)&str[needle]);
		needle++;
	}
	if (str[needle] == c)
		return ((char *)&str[needle]);
	return (NULL);
}
