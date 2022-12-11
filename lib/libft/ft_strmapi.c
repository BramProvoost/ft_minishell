/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 14:52:04 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:38:32 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Applies the function ’f’ to each character of the string ’s’, and passing 
	its index as first argument to create a new string (with malloc(3)) resulting
	from successive applications of ’f’.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	length;
	char			*new_s;

	if (!s || !f)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	new_s = (char *)malloc(sizeof(char) * (length + 1));
	if (!new_s)
		return (NULL);
	while (i < length)
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
