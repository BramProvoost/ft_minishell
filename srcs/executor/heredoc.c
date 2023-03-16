/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 19:36:26 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/22 20:04:02 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	create_heredoc_file(char *delimiter, char *file_name)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
	if (fd == ERROR || access(file_name, 0) != 0)
		return (file_error(file_name));
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (ERROR);
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

int	run_heredoc(t_cmd *cmd, t_env *env, char *delimiter)
{
	int	fd;

	fd = open(cmd->file->file_name, O_RDONLY);
	if (fd == ERROR)
		return (file_error(cmd->file->file_name));
	if (duplicate(fd, STDIN_FILENO) == ERROR)
		return (ERROR);
	ft_execute(cmd, env);
	if (unlink(cmd->file->file_name) == ERROR)
		return (file_error(cmd->file->file_name));
	free(delimiter);
	return (SUCCESS);
}

int	heredoc(t_cmd *cmd, t_env *env)
{
	char	*delimiter;

	while (cmd)
	{
		if (cmd->file->type == HEREDOC)
		{
			delimiter = ft_strdup(cmd->exec->cmd_args[0]);
			if (!delimiter)
				return (ERROR);
			if (create_heredoc_file(delimiter, cmd->file->file_name) == ERROR)
			{
				free(delimiter);
				return (ERROR);
			}
			if (run_heredoc(cmd, env, delimiter) == ERROR)
			{
				free(delimiter);
				return (ERROR);
			}
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}
