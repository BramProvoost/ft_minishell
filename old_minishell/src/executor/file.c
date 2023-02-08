/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   file.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/27 14:35:08 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/03 18:40:06 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	open_infile(char *file, t_data *data)
{
	int fd;

	if (!file)
		return ;
	fd = open(file, O_RDONLY, 0777);
	if (fd < 0)
		message_exit("open_infile faalt", 1);
	dup2(fd, data->infile);
	close(fd);
}

void	open_till(char *file, t_data *data, char *str)
{
	
	int fd;

	str++;
	if (!file)
		return ;
	fd = open(file, O_RDONLY, 0777);
	if (fd < 0)
		message_exit("open_till faalt", 1);
	dup2(fd, data->infile);
	close(fd);
}

void	open_outfile(char *file, t_data *data, int flag)
{
	int fd;
	int flags;

	flags = 0;
	if (!file || data)
		return ;
	if (flag == e_redirect_o)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (flag == e_append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(file, flags, 0644);
	if (fd < 0)
		message_exit("open_outfile faalt", 1);
	dup2(fd, data->outfile);
	close(fd);
}