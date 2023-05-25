/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_from_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:32:21 by bprovoos          #+#    #+#             */
/*   Updated: 2023/05/25 12:47:54 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	delete_cmds(t_cmd *cmd)
{
	t_cmd	*tmp_cmd;
	t_file	*tmp_file;

	while (cmd)
	{
		tmp_cmd = cmd;
		cmd = cmd->next;
		if (tmp_cmd->exec)
		{
			free(tmp_cmd->exec->cmd_path);
			free_2d(tmp_cmd->exec->cmd_args);
			free(tmp_cmd->exec);
		}
		while (tmp_cmd->file)
		{
			tmp_file = tmp_cmd->file;
			tmp_cmd->file = tmp_cmd->file->next;
			if (tmp_file)
				free(tmp_file);
		}
		free(tmp_cmd);
	}
}

char	**get_paths(t_env *env)
{
	int		i;
	char	*path;
	char	**paths;
	char	*tmp;

	i = 0;
	while (env->key && env->has_value && ft_strncmp("PATH", env->key, 4))
		env = env->next;
	if (env->key == NULL)
		error_exit(errno, "PATH not found");
	path = ft_strdup(env->value);
	if (!path)
		error_exit(errno, "malloc error");
	paths = ft_split(path, ':');
	if (!paths)
		error_exit(errno, "malloc error");
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
	free(path);
	return (paths);
}

char	**add_to_2d(char **old_arr, char *new_str)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (!old_arr)
	{
		new_arr = (char **)malloc(2 * sizeof(char *));
		new_arr[0] = ft_strdup(new_str);
		new_arr[1] = NULL;
		return (new_arr);
	}
	while (old_arr[i])
		i++;
	new_arr = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (old_arr[i])
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(new_str);
	new_arr[i + 1] = NULL;
	free_2d(old_arr);
	return (new_arr);
}

int	is_ready_adding_path(t_token *tokens)
{
	if (is_rederect(tokens->type) || tokens->type == PIPE)
		return (1);
	return (0);
}

t_cmd	*get_cmd_from_token(t_token *tokens, t_env *env)
{
	t_cmd	*cmd;
	char	**cmd_and_args;

	cmd = NULL;
	cmd_and_args = NULL;
	while (tokens)
	{
		if (tokens->type == CMD && tokens->value)
			cmd_and_args = add_to_2d(cmd_and_args, tokens->value);
		else if (tokens->type == WORD && tokens->value)
			cmd_and_args = add_to_2d(cmd_and_args, tokens->value);
		else if (tokens->type == FILE_T)
			file_to_t_cmd(&cmd, tokens);
		else if (is_ready_adding_path(tokens) && cmd_and_args)
		{
			path_and_cmd_to_t_cmd(&cmd, cmd_and_args, env);
			free_2d(cmd_and_args);
			cmd_and_args = NULL;
		}
		tokens = tokens->next;
	}
	if (cmd_and_args)
		path_and_cmd_to_t_cmd(&cmd, cmd_and_args, env);
	free_2d(cmd_and_args);
	return (cmd);
}
