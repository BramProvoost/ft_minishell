/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 11:42:17 by bramjr            #+#    #+#             */
/*   Updated: 2023/05/26 21:15:25 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/*
	Returns an integer greater than, equal to, or less than 0, according as the 
	string s1 is greater than, equal to, or less than the string s2.
	
	The comparison is done using unsigned characters, so that `\200' is greater 
	than `\0'.
*/
int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!str1[i] || !str2[i] || str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
