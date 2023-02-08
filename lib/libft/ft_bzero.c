/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:56:30 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:55:22 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Write n zeroed bytes to the string s. If n is zero, bzero() does nothing.
*/
void	ft_bzero(char *s, int n)
{
	ft_memset(s, '\0', n);
}
