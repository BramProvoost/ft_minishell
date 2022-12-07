/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 16:43:11 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 17:03:58 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
	Copies n bytes from memory area src to memory area dst. If dst and src 
	overlap, behavior is undefined. Applications in which dst and src might 
	overlap should use memmove(3) instead.
*/
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*pdest;
	unsigned char	*psrc;
	size_t			i;

	pdest = (unsigned char *)dest;
	psrc = (unsigned char *)src;
	i = 0;
	if (n != 0 && dest == src)
		return (dest);
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
