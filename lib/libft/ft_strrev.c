/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrev.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 10:22:44 by bprovoos      #+#    #+#                 */
/*   Updated: 2020/12/29 09:14:46 by bramjr        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *src, char *dst)
{
	int		i;
	int		len;
	char	temp;

	i = 0;
	len = ft_strlen(src) - 1;
	while (i < len / 2)
	{
		temp = src[i];
		dst[i] = src[len - i];
		dst[len - i] = temp;
		i++;
	}
	dst[len + 1] = '\0';
}
