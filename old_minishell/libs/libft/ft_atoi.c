/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:25:08 by bramjr        #+#    #+#                 */
/*   Updated: 2022/10/14 16:54:28 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	converts the string to a int representation.
*/
long	ft_atoi(const char *str)
{
	int		neg;
	long	num;
	int		i;

	i = 0;
	neg = 1;
	num = 0;
	while (str[i] != '\0' && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	if ((i > 19 || num >= 9223372036854775808ULL) && neg == 1)
		return (-1);
	if ((i > 19 || num >= 9223372036854775808ULL) && neg != 1)
		return (0);
	return (num * neg);
}
