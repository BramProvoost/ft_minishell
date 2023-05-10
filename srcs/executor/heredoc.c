/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/29 19:36:26 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/10 16:12:09 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	str_start_stop_with_quotes(char *str)
{
	int	i;
	int	start_quote;
	int	stop_quote;

	i = 0;
	start_quote = 0;
	stop_quote = 0;
	if (str[0] == '\'' || str[0] == '"')
		start_quote = str[0];
	while (str[i])
		i++;
	if (i == 0)
		return (0);
	else
		i--;
	if (str[i] == '\'' || str[i] == '"')
		stop_quote = str[i];
	return (start_quote != 0 && start_quote == stop_quote);
}

int	write_line_to_file(char *line, char *delimiter, int do_expand, int fd, t_env *env)
{
	if (!line)
		return (0);
	if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
	{
		free(line);
		return (0);
	}
	if (do_expand)
		line = expand(line , env);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}

int	create_heredoc_file(char *delimiter, char *file_name, t_env *env)
{
	int		fd;
	char	*line;
	int		do_expand;

	if (file_name != NULL)
	{
		do_expand = !str_start_stop_with_quotes(delimiter);
		if (!do_expand)
			delimiter = rm_quotes(delimiter);
		fd = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0700);
		if (fd == ERROR || access(file_name, 0) != 0)
			return (file_error(file_name));
		while (1)
		{
			line = readline("> ");
			if (write_line_to_file(line, delimiter, do_expand, fd, env) == 0)
				break ;
		}
		close(fd);
	}
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
				if (create_heredoc_file(file->delimiter, file->file_name, exec_data->env) == ERROR)
					return (ERROR);
			}
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (SUCCESS);
}