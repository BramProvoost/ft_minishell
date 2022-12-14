/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 19:26:18 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 17:12:34 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
	Copies bytes from string src to string dst. If the character c (as converted 
	to an unsigned char) occurs in the string src, the copy stops and a pointer 
	to the byte after the copy of c in the string dst is returned.

	Otherwise, n bytes are copied, and a NULL pointer is returned. The source and 
	destination strings should not overlap, as the behavior is undefined.
*/
void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	unsigned char	*pdes;
	unsigned char	*psrc;
	size_t			i;

	pdes = (unsigned char *)s1;
	psrc = (unsigned char *)s2;
	i = 0;
	while (n > 0)
	{
		*pdes = *psrc;
		if (*psrc == (unsigned char)c)
			return (pdes + 1);
		pdes++;
		psrc++;
		n--;
	}
	return (NULL);
}
