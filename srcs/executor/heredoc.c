/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:36:26 by edawood           #+#    #+#             */
/*   Updated: 2023/05/01 19:51:08 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

// char	name_heredoc_file(char *delimiter)
// {
// 	// save the delimiter address as a string with the delimiter as a name
// 	// return the string
	
	
	
// }

int	create_heredoc_file(char *delimiter, char *file_name)
{
	int		fd;
	char	*line;

	if (file_name != NULL)
	{
		fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
		if (fd == ERROR || access(file_name, 0) != 0)
			return (file_error(file_name));
	}
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (SUCCESS);
}

int	run_heredoc(t_file *file)
{
	int	fd;

	fd = open(file->file_name, O_RDONLY);
	unlink(file->file_name);
	return (fd);
}

int	heredoc(t_exec_data *exec_data)
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
				file->file_name = file->delimiter;
				if (create_heredoc_file(file->delimiter, file->file_name) == ERROR)
					return (ERROR);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
