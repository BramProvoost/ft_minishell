/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 10:48:18 by edawood       #+#    #+#                 */
/*   Updated: 2023/04/05 17:54:10 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	duplicate(int fd, int fileno)
{
	if (fd == fileno)
		return (SUCCESS);
	if (dup2(fd, fileno) == ERROR)
	{
		perror(ft_itoa(errno));
		g_exit_status = errno;
		return (ERROR);
	}
	return (SUCCESS);
}

static int	open_file(char *file_name, int type)
{
	int	fd;

	if (type == OUTPUT)
		fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
	if (type == APPEND)
		fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0700);
	if (fd == ERROR || access(file_name, 0) != 0)
		return (file_error(file_name));
	return (fd);
}

int	redirect_input(t_cmd *cmd, t_env *env, int fd)
{
	if (cmd->file == NULL)
		return (duplicate(fd, STDIN_FILENO));
	if (cmd->file->type == INPUT_SINGLE)
	{
		fd = open(cmd->file->file_name, O_RDONLY);
		if (fd == ERROR)
			return (file_error(cmd->file->file_name));
	}
	else if (cmd->file->type == HEREDOC)
		heredoc(cmd, env);
	return (duplicate(fd, STDIN_FILENO));
}

int	redirect_output(t_exec_data *exec_data)
{
	int	fd;

	fd = 0;
	if (exec_data->is_pipe == true)
		return (duplicate(exec_data->pipe_fds[WRITE], STDOUT_FILENO));
	if (exec_data->cmd->file == NULL)
		return (SUCCESS);
	if (exec_data->cmd->file->type == OUTPUT_SINGLE)
	{
		fd = open_file(exec_data->cmd->file->file_name, OUTPUT);
		return (duplicate(fd, STDOUT_FILENO));
	}
	else if (exec_data->cmd->file->type == OUTPUT_APPEND)
	{
		fd = open_file(exec_data->cmd->file->file_name, APPEND);
		return (duplicate(fd, STDOUT_FILENO));
	}
	else if (exec_data->cmd->file->type == HEREDOC)
		heredoc(exec_data->cmd, exec_data->env);
	return (SUCCESS);
}

void	close_fds(int *pipe_fds, int fd_in, bool is_pipe)
{
	if (is_pipe == true)
	{
		if (close(pipe_fds[WRITE]) == ERROR)
		{
			ft_putstr_fd("write fd close failed\n", 2);
			exit(1);
		}
	}
	if (fd_in > 0)
	{
		if (close(fd_in) == ERROR)
		{
			ft_putstr_fd("prev fd close failed\n", 2);
			exit(1);
		}
	}
}
