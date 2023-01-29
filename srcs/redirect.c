/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:48:18 by edawood           #+#    #+#             */
/*   Updated: 2023/01/29 13:36:51 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

int duplicate(t_args *args, int fd, int fileno)
{
    if (dup2(fd, fileno) == ERROR)
    {
		perror(ft_itoa(errno));
		args->status_code = errno;
		return (ERROR);
	}
	if (fd == READ && fd == WRITE)
		close(fd);
	return (SUCCESS);
}

int redirect_input(t_args *args, t_file *file, int fd)
{
    if (file->type == INPUT_SINGLE)
    {
        fd = open(file->file_name, O_RDONLY);
        if (fd == ERROR)
            return (file_error(file->file_name));
    }
    else if (file->type == INPUT_DOUBLE)
        printf("it's heredoc\n");
    return (duplicate(args, fd, STDIN_FILENO));
}

int redirect_output(t_args *args, t_file *file, int fd)
{
    if (file->type == OUTPUT_SINGLE)
    {
        fd = open(file->file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
        if (fd == ERROR || access(file->file_name, 0) != 0)
            return (file_error(file->file_name));
    }
    else if (file->type == OUTPUT_DOUBLE)
        printf("it's herdoc\n");
    return (duplicate(args, fd, STDOUT_FILENO));
}

void	close_fds_run_with_pipes(int *pipe_fds, int fd_in)
{
	if (fd_in > 0)
	{
		if (close(fd_in) == ERROR)
        {
            ft_putstr_fd("close failed\n", 2);
            exit(1);
        }
	}
	if (close(pipe_fds[WRITE]) == ERROR)
    {
        ft_putstr_fd("close failed\n", 2);
        exit(1);
    }
}