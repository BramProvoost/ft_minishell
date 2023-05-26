/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:25:00 by edawood           #+#    #+#             */
/*   Updated: 2023/05/26 18:38:39 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_files(t_exec_data *exec_data)
{
	t_cmd	*cmd;
	t_file	*file;

	cmd = exec_data->cmd;
	file = exec_data->cmd->file;
	while (cmd)
	{
		while (file)
		{
			if (file->type == HEREDOC && file->file_name != NULL)
				free(file->file_name);
			file = file->next;
		}
		cmd = cmd->next;
	}
}

bool	open_heredoc(char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_RDWR, 0700);
	if (fd == ERROR)
		return (false);
	close(fd);
	return (true);
}

void	check_open(char *file_name, t_exec_data *exec_data)
{
	int		fd;

	fd = open(file_name, O_TRUNC | O_RDWR, 0700);
	if (fd == ERROR || access(file_name, 0) != 0)
	{
		close(fd);
		error_heredoc(file_name, exec_data);
	}
	return (fd);
}

int	expand_heredoc(t_file *file)
{
	int	do_expand;

	do_expand = !str_start_stop_with_quotes(file->delimiter);
	if (!do_expand)
		file->delimiter = rm_quotes(file->delimiter);
	return (do_expand);
}

void	read_loop(t_exec_data *exec_data, int fd, int do_expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (line[0] == '\0')
			continue ;
		if (write_line_to_file(exec_data, line, \
			do_expand, fd) == 0)
			break ;
		free(line);
	}
}
