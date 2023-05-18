/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 19:36:26 by edawood           #+#    #+#             */
/*   Updated: 2023/05/18 16:40:00 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

bool	has_heredoc(t_cmd *cmd)
{
	t_file	*file;

	file = cmd->file;
	while (file)
	{
		if (file->type == HEREDOC)
			return (true);
		file = file->next;
	}
	return (false);
}

char	*heredoc_file_named(uintptr_t n)
{
	char	*str;
	char	*hex;
	int		i;

	hex = "0123456789abcdef";
	i = 0;
	str = malloc(sizeof(char) * 100);
	if (!str)
		return (NULL);
	while (n)
	{
		str[i] = hex[n % 16];
		n /= 16;
		i++;
	}
	str[i] = '\0';
	return (str);
}

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

bool	create_file(t_exec_data *exec_data)
{
	t_file	*file;
	t_cmd	*cmd;
	int		fd;

	file = exec_data->cmd->file;
	cmd	= exec_data->cmd;
	while (cmd)
	{
		while (file)
		{
			if (file->type == HEREDOC)
			{
				file->file_name = heredoc_file_named((uintptr_t)file->delimiter);
				fd = open(file->file_name, O_WRONLY | O_CREAT | O_RDONLY, 0700);
				if (fd == ERROR)
					return (false);
				close(fd);
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
		do_expand = !str_start_stop_with_quotes(file->delimiter);
		if (!do_expand)
			file->delimiter = rm_quotes(file->delimiter);
		fd = open(file->file_name, O_TRUNC | O_RDWR, 0700);
		if (fd == ERROR || access(file->file_name, 0) != 0)
			error_heredoc(file->file_name, exec_data);
		while (1)
		{
			line = readline("> ");
			if (write_line_to_file(line, file->delimiter, do_expand, fd, exec_data->env) == 0)
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
}

void	unlink_heredoc_files(t_exec_data *exec_data)
{
	t_cmd	*cmd;
	t_file	*file;

	cmd = exec_data->cmd;
	file = cmd->file;
	while (cmd)
	{
		while (file)
		{
			unlink(file->file_name);
			file = file->next;
		}
		cmd = cmd->next;
	}
}

int	heredoc(t_exec_data *exec_data)
{
	t_file	*file;
	t_cmd	*cmd;
	pid_t	pid;
	int		wifexited;

	file = exec_data->cmd->file;
	cmd = exec_data->cmd;
	create_file(exec_data);
	fprintf(stderr, "heredoc\n");
	pid = fork();
	if (pid == ERROR)
		ft_error();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (cmd)
		{
			while (file)
			{
				if (file->type == HEREDOC)
					create_heredoc_file(file, exec_data);
				file = file->next;
			}
			cmd = cmd->next;
		}
		exit(0);
	}
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