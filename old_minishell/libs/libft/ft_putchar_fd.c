/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/08 15:53:53 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/10/14 16:46:25 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

/*
	Outputs the character ’c’ to the given file descriptor.
*/
int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}
