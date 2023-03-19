/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:05:22 by edawood           #+#    #+#             */
/*   Updated: 2023/03/19 18:02:05 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

void	child_process(t_cmd *cmd, t_env *env, int fd[2], int prev_fd)
{
	if (redirect_input(cmd, env, prev_fd) != SUCCESS)
	{
		close(fd[0]);
		exit(g_last_pid);
	}
	if (cmd->next)
	{
		if (redirect_output(cmd, env, prev_fd) != SUCCESS)
		{
			close(fd[1]);
			exit(g_last_pid);
		}
	}
	ft_execute(cmd, env);
}

void	ft_execute(t_cmd *cmd, t_env *env)
{
	char	**env_list;

	env_list = env_to_list(env);
	if (execve(cmd->exec->cmd_path, cmd->exec->cmd_args, env_list) == ERROR)
		error_exit(errno, cmd->exec->cmd_args[0]);
}
