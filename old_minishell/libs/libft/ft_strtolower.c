/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtolower.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/23 09:59:37 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:52:33 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Set all characters in the string to lower case
*/
char	*ft_strtolower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
	return (str);
}

/*
// gcc -Wall -Werror -Wextra ft_strtolower.c ft_tolower.c ft_isupper.c 
ft_strdup.c ft_strlen.c && ./a.out && rm a.out

#include <stdio.h>

int	main(void)
{
	char	*str;

	str = ft_strdup("aAbBcC");
	str = ft_strtolower(str);
	printf("%s\n", str);
	return (0);
}
*/
