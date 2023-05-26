/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:07:04 by edawood           #+#    #+#             */
/*   Updated: 2023/05/26 18:42:44 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	close_main_fds(int fd_in, int fd_out)
{
	close(fd_in);
	close(fd_out);
}

int	prepare_to_pipe_and_fork(t_exec_data *exec_data, int fd)
{
	pid_t	fork_pid;

	exec_data->is_pipe = has_pipe(exec_data->cmd);
	if (exec_data->is_pipe && pipe(exec_data->pipe_fds) == ERROR)
		ft_error();
	fork_pid = fork();
	if (fork_pid == ERROR)
	{
		close_pipes(exec_data->pipe_fds);
		ft_error();
	}
	if (fork_pid == CHILD)
		child_process(exec_data, fd);
	close_fds(exec_data->pipe_fds, fd, exec_data->is_pipe);
	set_cmd_to_next(exec_data);
	if (exec_data->is_pipe == false)
		return (fork_pid);
	return (prepare_to_pipe_and_fork(exec_data, exec_data->pipe_fds[READ]));
}

static pid_t	simple_command(t_exec_data *exec_data, t_env **env)
{
	pid_t	fork_pid;

	fork_pid = -1;
	if (redirect_in_simple_cmd(exec_data) == ERROR)
		return (fork_pid);
	if (exec_data->cmd->exec == NULL)
		return (fork_pid);
	if (execute_built_in_cmd(exec_data, \
		exec_data->cmd->exec->cmd_args[0], true, env) == SUCCESS)
		return (fork_pid);
	else
	{
		fork_pid = fork();
		if (fork_pid == ERROR)
			ft_error();
		if (fork_pid == CHILD)
			ft_execute(exec_data);
	}
	return (fork_pid);
}

void	executor(t_cmd *cmd, t_token *tokens, t_env **env_double_ptr)
{
	pid_t		last_pid;
	t_exec_data	exec_data;
	int			fd_in;
	int			fd_out;
	t_env		*env;

	last_pid = 0;
	env = *env_double_ptr;
	if (!cmd)
		return ;
	exec_data_init(&exec_data, cmd, tokens, env);
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (exec_data.has_heredoc == true)
	{
		if (heredoc(&exec_data) == ERROR)
			return (NULL, close_main_fds(fd_in, fd_out));
	}
	if (exec_data.is_pipe == true)
		last_pid = prepare_to_pipe_and_fork(&exec_data, STDIN_FILENO);
	else
		last_pid = simple_command(&exec_data, env_double_ptr);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_main_fds(fd_in, fd_out);
	wait_for_pids(last_pid);
}
