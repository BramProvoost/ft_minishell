/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:52:12 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 13:45:36 by edawood          ###   ########.fr       */
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

char	*heredoc_file_named(unsigned long n)
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

void	unlink_heredoc_files(t_exec_data *exec_data)
{
	t_cmd	*cmd;
	t_file	*file;
	int		fd;

	cmd = exec_data->cmd;
	file = cmd->file;
	while (cmd)
	{
		while (file)
		{
			fd = open(file->file_name, O_RDONLY);
			if (fd != ERROR)
				unlink(file->file_name);
			close(fd);
			file = file->next;
		}
		cmd = cmd->next;
	}
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

void	heredoc_child(t_exec_data *exec_data)
{
	t_file	*file;
	t_cmd	*cmd;

	file = exec_data->cmd->file;
	cmd = exec_data->cmd;
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
	_exit(0);
}
