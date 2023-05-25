/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 10:48:18 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 11:15:30 by edawood          ###   ########.fr       */
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

	if (file_name == NULL || file_name[0] == '\0')
		return (ERROR);
	if (type == OUTPUT)
		fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
	if (type == APPEND)
		fd = open(file_name, O_CREAT | O_APPEND | O_RDWR, 0700);
	if (fd == ERROR || access(file_name, 0) != 0)
		return (file_error(file_name));
	return (fd);
}

int	redirect_input(t_exec_data *exec_data, int fd)
{
	t_file	*tmp;

	tmp = exec_data->cmd->file;
	while (tmp)
	{
		if (fd != STDIN_FILENO && (tmp->type == HEREDOC || tmp->type == INPUT_SINGLE))
			close(fd);
		if (tmp->type == INPUT_SINGLE)
		{
			fd = open(tmp->file_name, O_RDONLY);
			if (fd == ERROR)
				return (file_error(tmp->file_name));
		}
		if (fd == ERROR)
			return (error_ambiguous());
		if (tmp->type == HEREDOC)
			run_heredoc(tmp);
		tmp = tmp->next;
	}
	return (duplicate(fd, STDIN_FILENO));
}

int	redirect_output(t_exec_data *exec_data)
{
	int	fd;
	t_file	*tmp;

	tmp = exec_data->cmd->file;
	fd = STDOUT_FILENO;
	if (exec_data->is_pipe == true)
		fd = exec_data->pipe_fds[WRITE];
	while (tmp)
	{
		if (fd != STDOUT_FILENO && (tmp->type == OUTPUT_SINGLE || tmp->type == OUTPUT_APPEND))
			close(fd);
		if (tmp->type == OUTPUT_SINGLE)
			fd = open_file(tmp->file_name, OUTPUT);
		else if (tmp->type == OUTPUT_APPEND)
			fd = open_file(tmp->file_name, APPEND);
		if (fd == ERROR)
			return (error_ambiguous());
		tmp = tmp->next;
	}
	return (duplicate(fd, STDOUT_FILENO));
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
