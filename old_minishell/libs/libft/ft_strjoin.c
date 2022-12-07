/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/01 21:34:14 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:30:32 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Allocates (with malloc(3)) and returns a new string, which is the result of 
	the concatenation of ’s1’ and ’s2’.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len1 = ft_strlen(s1) + 1;
	len2 = ft_strlen(s2);
	result = (char *)malloc(sizeof(char) * (len1 + len2));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1);
	ft_strlcat(result, s2, len1 + len2);
	return (result);
}
