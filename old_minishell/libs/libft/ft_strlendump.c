/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlendump.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/30 12:19:23 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/09/30 12:28:16 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strlendump(const char *str, size_t length)
{
	char	*temp;

	temp = (char *)malloc(sizeof(*str) * (length + 1));
	if (!temp)
		return (NULL);
	temp[length] = '\0';
	while (length > 0)
	{
		length--;
		temp[length] = str[length];
	}
	return (temp);
}
