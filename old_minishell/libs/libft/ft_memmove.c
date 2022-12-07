/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:50:04 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 20:55:30 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
	Copies len bytes from string src to string dst. The two strings may overlap; 
	the copy is always done in a non-destructive manner.
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*pdst;
	unsigned char	*psrc;

	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	i = 0;
	if (len > 0 && pdst == psrc)
		return (pdst);
	while (i < len)
	{
		if (dst < src)
			pdst[i] = psrc[i];
		else
			pdst[len - i - 1] = psrc[len - i - 1];
		i++;
	}
	return (pdst);
}
