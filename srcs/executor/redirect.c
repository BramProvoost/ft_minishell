/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 10:48:18 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:31:15 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	duplicate(t_args *args, int fd, int fileno)
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

int	redirect_input(t_cmd *cmd, t_args *args, int fd)
{
	if (cmd->file->type == INPUT_SINGLE)
	{
		fd = open(cmd->file->file_name, O_RDONLY);
		if (fd == ERROR)
			return (file_error(cmd->file->file_name));
	}
	else if (cmd->file->type == HEREDOC)
		heredoc(cmd, args);
	return (duplicate(args, fd, STDIN_FILENO));
}

int	redirect_output(t_cmd *cmd, t_args *args, int fd)
{
	if (cmd->file->type == OUTPUT_SINGLE)
	{
		fd = open(cmd->file->file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
		if (fd == ERROR || access(cmd->file->file_name, 0) != 0)
			return (file_error(cmd->file->file_name));
	}
	else if (cmd->file->type == OUTPUT_APPEND)
	{
		fd = open(cmd->file->file_name, O_CREAT | O_APPEND | O_RDWR, 0700);
		if (fd == ERROR || access(cmd->file->file_name, 0) != 0)
			return (file_error(cmd->file->file_name));
	}
	else if (cmd->file->type == HEREDOC)
		heredoc(cmd, args);
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