/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_extras.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:25:00 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 13:30:26 by edawood          ###   ########.fr       */
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
			if (file->type == HEREDOC)
				free(file->file_name);
			file = file->next;
		}
		cmd = cmd->next;
	}
}

bool	open_heredoc(char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_RDONLY, 0700);
	if (fd == ERROR)
		return (false);
	close(fd);
	return (true);
}
