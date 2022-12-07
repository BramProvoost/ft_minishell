/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isalpha.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:13:08 by bramjr        #+#    #+#                 */
/*   Updated: 2021/05/27 17:59:20 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return (ft_islower(c) || ft_isupper(c));
}
