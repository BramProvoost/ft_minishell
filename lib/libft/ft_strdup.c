/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:38:05 by bprovoos          #+#    #+#             */
/*   Updated: 2023/04/20 18:28:03 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char			*temp;
	unsigned long	len;
	unsigned long	i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	temp = (char *)malloc(len + 1);
	if (!temp)
		return (NULL);
	i = len;
	len = 0;
	while (len < i)
	{
		temp[len] = str[len];
		len++;
	}
	temp[len] = '\0';
	return (temp);
}
