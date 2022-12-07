/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/06 13:50:30 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/09/23 11:23:22 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_number_length(long number, int base)
{
	int	length;

	if (number == 0)
		return (1);
	length = 0;
	if (number < 0 && base == 10)
	{
		length++;
	}	
	while (number != 0)
	{
		number /= base;
		length++;
	}
	return (length);
}

char	*ft_itoa_base(long number, int base)
{
	int			needle;
	char		*result;
	const char	*strbase = "0123456789abcdef";

	if (base < 2 || base > 16)
		return (NULL);
	needle = get_number_length(number, base);
	result = malloc(sizeof(char) * needle + 1);
	if (!result)
		return (NULL);
	result[needle] = '\0';
	if (number < 0)
	{
		result[0] = '-';
		number *= -1;
	}
	else if (number == 0)
		result[0] = '0';
	while (number > 0)
	{
		needle--;
		result[needle] = strbase[number % base];
		number /= base;
	}
	return (result);
}

/*
// gcc -Wall -Werror -Wextra ft_itoa_base.c ft_strlen.c && ./a.out && rm a.out

#include <stdio.h>

int	main(void)
{
	char	*str;
	int		nr;

	nr = -2147483648;
	str = NULL;
	str = ft_itoa_base((unsigned int)nr, 2);
	printf("b: %s\n", str);
	str = ft_itoa_base(nr, 10);
	printf("d: %s\n", str);
	printf("d: %d\n", nr);
	str = ft_itoa_base((unsigned int)nr, 16);
	printf("x: %s\n", str);
	printf("x: %x\n", nr);
	printf("p: %p\n", &str);
	printf("p: 0x%s\n", ft_itoa_base((unsigned long)&str, 16));
	free(str);
	str = NULL;
	return (0);
}
*/
