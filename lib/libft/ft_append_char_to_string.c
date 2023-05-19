/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_append_char_to_string.c                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/11 16:31:44 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/11 16:34:25 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_append_char_to_string(char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (!str)
	{
		new_str = (char *)malloc(2);
		if (!new_str)
			return (NULL);
		new_str[0] = c;
		new_str[1] = '\0';
		return (new_str);
	}
	len = ft_strlen(str);
	new_str = (char *)malloc(len + 2);
	if (!new_str)
		return (str);
	ft_strlcpy(new_str, str, len + 1);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}
