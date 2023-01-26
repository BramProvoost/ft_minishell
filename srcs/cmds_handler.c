/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:05:22 by edawood           #+#    #+#             */
/*   Updated: 2023/01/26 12:15:16 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

char	*get_full_cmd(char *cmd, char **paths)
{
	int		i;
	char	*temp_path;

	i = 0;
	if (cmd && *cmd == '\0')
		return (NULL);
	if (access(cmd, X_OK) == SUCCESS)
		return (cmd);
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], cmd);
		if (!temp_path)
		{
			errno = ENOMEM;
			return (NULL);
		}
		if (access(temp_path, X_OK) == SUCCESS)
			return (temp_path);
		i++;
	}
	free_2d(paths);
	return (NULL);
}

void	child_process(t_cmd *cmd, t_args *args, int fd[2], int prev_fd)
{
	if (!redirect_input(args, cmd->file, prev_fd))
	{
		close(fd[0]);
		exit(args->status_code);
	}
	if (cmd->next)
		if (!redirect_output(args, cmd->file, prev_fd))
		{
			close(fd[1]);
			exit(args->status_code);
		}
	ft_execute(cmd, args);
}

char	**env_to_list(t_args *args)
{
	char	**env_list;
	int		i;

	i = 0;
	env_list = (char **)malloc(sizeof(char *) * (args->env_len + 1));
	if (!env_list)
	{
		errno = ENOMEM;
		return (NULL);
	}
	while (i < args->env_len)
	{
		env_list[i] = ft_strjoin(args->env[i].key, "=");
		if (!env_list[i])
		{
			errno = ENOMEM;
			return (NULL);
		}
		env_list[i] = ft_strjoin(env_list[i], args->env[i].value);
		if (!env_list[i])
		{
			errno = ENOMEM;
			return (NULL);
		}
		i++;
	}
	env_list[i] = NULL;
	return (env_list);
}

void	ft_execute(t_cmd *cmd, t_args *args)
{
	char	*full_cmd;
	char	**env_list;
	char	**cmd1;
	
	cmd1 = ft_split(cmd->arg, ' ');
	if (!cmd1 || !*cmd1 || args->paths == NULL)
		error_exit(errno, cmd->arg);
	full_cmd = get_full_cmd(*cmd1, args->paths);
	env_list = env_to_list(args);
	if (!full_cmd)
		error_cmd_not_found(cmd->arg);
	if (execve(full_cmd, cmd1, env_list) == ERROR)
		error_exit(errno, cmd1[0]);
}
