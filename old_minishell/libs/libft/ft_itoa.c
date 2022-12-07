/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/30 18:31:16 by bramjr        #+#    #+#                 */
/*   Updated: 2022/10/14 16:33:58 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	build_string(char *output, int input, int is_negative, int len)
{
	int		i;

	i = 0;
	if (is_negative)
	{
		output[i] = '-';
		i++;
	}
	output[len] = '\0';
	while (i < len)
	{
		len--;
		output[len] = '0' + (input % 10);
		input /= 10;
	}
}

int	get_len_of_int(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/*
	Allocates (with malloc(3)) and returns a string representing the integer 
	received as an argument.
*/
char	*ft_itoa(int n)
{
	char	*result;
	int		is_negative;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	is_negative = 0;
	if (n < 0)
	{
		n = -n;
		is_negative = 1;
	}
	len = get_len_of_int(n) + is_negative;
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	build_string(result, n, is_negative, len);
	return (result);
}
