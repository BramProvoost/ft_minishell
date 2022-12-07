/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 13:07:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/04/20 09:25:43 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *str, int c)
{
	char	needle;
	int		counter;

	counter = 0;
	needle = (unsigned char)c;
	while (str[counter])
		counter++;
	if (str[counter] == needle)
		return ((char *)&str[counter]);
	counter--;
	while (counter >= 0)
	{
		if (str[counter] == needle)
			return ((char *)&str[counter]);
		counter--;
	}
	return (NULL);
}
