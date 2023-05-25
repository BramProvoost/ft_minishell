/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:29:03 by bprovoos          #+#    #+#             */
/*   Updated: 2023/05/25 12:11:58 by edawood          ###   ########.fr       */
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

t_cmd	*init_cmd_for_file(t_cmd **cmd, t_token *token)
{
	if (!*cmd)
		*cmd = new_t_cmd();
	if (token->prev && token->prev->prev && token->prev->prev->type == PIPE)
		add_t_cmd_back(*cmd);
	return (*cmd);
}

void	file_to_t_cmd(t_cmd **cmd, t_token *tokens)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;

	tmp_cmd = init_cmd_for_file(cmd, tokens);
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
