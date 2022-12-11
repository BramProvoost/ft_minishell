/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_realloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/12 19:23:03 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/11/05 16:19:15 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "unistd.h"

void	*ft_realloc(void *ptr, size_t size)
{	
	void	*temp;

	temp = ft_calloc(1, size);
	if (ptr == NULL)
		return (temp);
	ft_strlcpy(temp, ptr, size);
	free(ptr);
	return (temp);
}

/*
gcc -Wall -Werror -Wextra -g -fsanitize=address ft_realloc.c ft_strlcpy.c
ft_strlcat.c ** ft_calloc.c ft_bzero.c ft_memset.c && ./a.out
*/

/*
int	main(void)
{
	char	*p1;
	int		m1;
	int		m2;

	m1 = 5;
	m2 = 7;
	p1 = (char *)malloc(m1 + 1);
	ft_strlcpy(p1, "It's ", m1 + 1);
	p1 = (char *)ft_realloc(p1, m1 + m2 + 1);
	ft_strlcat(p1, "Working", m1 + m2 + 1);
	printf("%s\n", p1);
	free(p1);
	return (0);
}
*/
