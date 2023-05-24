/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmds_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 12:05:22 by edawood       #+#    #+#                 */
/*   Updated: 2023/05/24 17:21:59 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*get_full_cmd(char *cmd, char **paths)
{
	int		i;
	char	*temp_path;

	i = 0;
	if (cmd && *cmd == '\0')
	{
		free_2d(paths);
		return (NULL);
	}
	if (access(cmd, X_OK) == SUCCESS)
	{
		free_2d(paths);
		return (ft_strdup(cmd));
	}
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], cmd);
		if (!temp_path)
		{
			errno = ENOMEM;
			return (NULL);
		}
		if (access(temp_path, X_OK) == SUCCESS)
		{
			free_2d(paths);
			return (temp_path);
		}
		i++;
		free(temp_path);
	}
	free_2d(paths);
	return (NULL);
}

void	child_process(t_exec_data *exec_data, int prev_fd)
{
	if (exec_data->is_pipe == true)
		close (exec_data->pipe_fds[READ]);
	if (redirect_input(exec_data, prev_fd) != SUCCESS)
		exit(g_exit_status);
	if (exec_data->cmd)
	{
		if (redirect_output(exec_data) != SUCCESS)
			exit(g_exit_status);
	}
	if (exec_data->cmd->exec != NULL)
		ft_execute(exec_data);
	else
		exit(g_exit_status);
}

void	ft_execute(t_exec_data *exec_data)
{
	char	**env_list;

	if (execute_built_in_cmd(exec_data, exec_data->cmd->exec->cmd_args[0], false) == SUCCESS)
		exit(g_exit_status);
	env_list = env_to_list(exec_data->env);
	execve(exec_data->cmd->exec->cmd_path, \
			exec_data->cmd->exec->cmd_args, env_list);
	error_cmd_not_found(exec_data->cmd->exec->cmd_args[0]);
}
