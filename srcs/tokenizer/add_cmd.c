/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:29:03 by bprovoos          #+#    #+#             */
/*   Updated: 2023/05/19 19:55:12 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	path_and_cmd_to_t_cmd(t_cmd **cmd, char **split_cmd_and_args,
			t_env *env)
{
	t_cmd	*tmp;
	char	*path_and_cmd;

	if (!*cmd)
		*cmd = new_t_cmd();
	else if ((*cmd)->file == NULL || (*cmd)->exec)
		add_t_cmd_back(*cmd);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (is_buld_in_cmd(split_cmd_and_args[0]))
		path_and_cmd = ft_strdup(split_cmd_and_args[0]);
	else
		path_and_cmd = get_full_cmd(split_cmd_and_args[0], get_paths(env));
	tmp->exec = new_t_exec();
	tmp->exec->cmd_path = ft_strdup(path_and_cmd);
	free(path_and_cmd);
	if (ft_strncmp(split_cmd_and_args[0], "export", 7) != 0)
		rm_quotes_from_2d_array(split_cmd_and_args);
	tmp->exec->cmd_args = ft_strdup2d(split_cmd_and_args);
}

// t_file	*add_new_file(t_cmd *tmp_cmd)
// {
// 	t_file	*tmp_file;

// 	tmp_file = tmp_cmd->file;
// 	if (!tmp_file)
// 	{
// 		tmp_cmd->file = new_t_file();
// 		tmp_file = tmp_cmd->file;
// 	}
// 	else
// 	{
// 		while (tmp_file->next)
// 			tmp_file = tmp_file->next;
// 		tmp_file->next = new_t_file();
// 		tmp_file = tmp_file->next;
// 	}
// 	return (tmp_file);
// }

void	file_to_t_cmd(t_cmd **cmd, t_token *tokens)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;

	if (!*cmd)
		*cmd = new_t_cmd();
	tmp_cmd = *cmd;
	while (tmp_cmd && tmp_cmd->next)
		tmp_cmd = tmp_cmd->next;
	tmp_file = tmp_cmd->file;
	if (!tmp_file)
	{
		tmp_cmd->file = new_t_file();
		tmp_file = tmp_cmd->file;
	}
	else
	{
		while (tmp_file->next)
			tmp_file = tmp_file->next;
		tmp_file->next = new_t_file();
		tmp_file = tmp_file->next;
	}
	tmp_file->type = tokens->prev->type;
	if (tokens->prev->type == HEREDOC)
		tmp_file->delimiter = tokens->value;
	else
		tmp_file->file_name = tokens->value;
}

void	temp_t_cmd_printer(t_cmd *cmd, char *header)
{
	int		i;
	int		j;
	t_file	*tmp_file;

	i = 0;
	printf(BLUE"%s"NC"\n", header);
	while (cmd)
	{
		if (cmd->exec)
		{
			if (cmd->exec->cmd_path)
				printf(GRAY"cmd[%d]->exec->cmd_path = '"GREEN"%s"GRAY"'"NC"\n", i, cmd->exec->cmd_path);
			if (cmd->exec->cmd_args)
			{
				j = 0;
				while (cmd->exec->cmd_args[j])
				{
					printf(GRAY"cmd[%d]->exec->cmd_args[%d] = '"GREEN"%s"GRAY"'"NC"\n", i, j, cmd->exec->cmd_args[j]);
					j++;
				}
			}
		}
		tmp_file = cmd->file;
		j = 0;
		while (tmp_file)
		{
			printf(GRAY"cmd[%d]->file[%d]->type = '"GREEN"%s"GRAY"'"NC"\n", i, j, temp_type_to_string(tmp_file->type));
			printf(GRAY"cmd[%d]->file[%d]->file_name = '"GREEN"%s"GRAY"'"NC"\n", i, j, tmp_file->file_name);
			printf(GRAY"cmd[%d]->file[%d]->delimiter = '"GREEN"%s"GRAY"'"NC"\n", i, j, tmp_file->delimiter);
			tmp_file = tmp_file->next;
			j++;
		}
		cmd = cmd->next;
		i++;
	}
	printf(BLUE"End %s"NC"\n", header);
}
