/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 19:36:26 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/27 15:28:46 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	write_line_to_file(t_exec_data *exec_data, char *line, \
						int do_expand, int fd)
{
	t_file	*file;
	char	*tmp;

	file = exec_data->cmd->file;
	if (!line)
	{
		free(line);
		free(file->file_name);
		return (0);
	}
	if (ft_strncmp(line, file->delimiter, ft_strlen(file->delimiter) + 1) == 0)
	{
		free(line);
		return (0);
	}
	tmp = line;
	if (do_expand)
	{
		line = expand(tmp, exec_data->env);
		free(tmp);
	}
	write (fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

bool	create_file(t_exec_data *exec_data)
{
	t_file	*file;
	t_cmd	*cmd;

	file = exec_data->cmd->file;
	cmd = exec_data->cmd;
	while (cmd)
	{
		while (file)
		{
			if (file->type == HEREDOC)
			{
				file->file_name = \
					heredoc_file_named((unsigned long)file->delimiter);
				if (!open_heredoc(file->file_name))
					return (false);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (true);
}

int	create_heredoc_file(t_file *file, t_exec_data *exec_data)
{
	int		fd;
	char	*line;
	int		do_expand;

	if (file->file_name != NULL)
	{
		do_expand = expand_heredoc(file);
		fd = check_open(file->file_name, exec_data);
		while (1)
		{
			line = readline("> ");
			if (check_line(line))
				break ;
			if (line[0] == '\0')
				continue ;
			if (write_line_to_file(exec_data, line, \
				do_expand, fd) == 0)
				break ;
		}
		close(fd);
	}
	return (SUCCESS);
}

void	run_heredoc(t_file *file)
{
	int	fd;

	fd = open(file->file_name, O_RDONLY);
	unlink(file->file_name);
	dup2(fd, STDIN_FILENO);
	free(file->file_name);
	close(fd);
}

int	heredoc(t_exec_data *exec_data)
{
	pid_t	pid;
	int		wifexited;

	create_file(exec_data);
	pid = fork();
	if (pid == ERROR)
		ft_error();
	if (pid == 0)
		heredoc_child(exec_data);
	signal(SIGINT, heredoc_signal_handler);
	waitpid(pid, &wifexited, 0);
	init_signals();
	if (WEXITSTATUS(wifexited) == 1 || WIFSIGNALED(wifexited))
	{
		if (WIFSIGNALED(wifexited))
			write(1, "\n", 1);
		unlink_heredoc_files(exec_data);
		return (ERROR);
	}
	return (SUCCESS);
}
