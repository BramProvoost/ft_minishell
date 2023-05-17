/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 18:47:59 by edawood           #+#    #+#             */
/*   Updated: 2023/05/17 22:39:25 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*heredoc_file(uintptr_t n)
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

int	heredoc_child(t_exec_data *exec_data)
{
	t_cmd	*cmd;
	t_file	*file;

	cmd = exec_data->cmd;
	file = cmd->file;
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

int	write_line_to_file(t_exec_data *exec_data, \
						char *line, int do_expand, int fd)
{
	t_file	*file;

	file = exec_data->cmd->file;
	if (!line)
		return (0);
	if (ft_strncmp(line, file->delimiter, ft_strlen(file->delimiter)) == 0)
	{
		free(line);
		return (0);
	}
	if (do_expand)
		line = expand(line, exec_data->env);
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	free(line);
	return (1);
}
