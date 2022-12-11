/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/10 21:38:05 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/09/30 11:37:41 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*temp;
	unsigned long	len;
	unsigned long	i;

	len = ft_strlen(str);
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	i = len;
	len = 0;
	while (len < i)
	{
		temp[len] = str[len];
		len++;
	}
	temp[len] = '\0';
	return (temp);
}
