/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 16:31:27 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:48:24 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Outputs the string ’s’ to the given file descriptor followed by a newline.
*/
int	ft_putendl_fd(char *str, int fd)
{
	int	i;

	i = ft_putstr_fd(str, fd);
	i += ft_putchar_fd('\n', fd);
	return (i);
}
