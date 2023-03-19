/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:07:04 by edawood           #+#    #+#             */
/*   Updated: 2023/03/19 18:04:34 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	prepare_to_pipe_and_fork(t_cmd *cmd, t_env *env)
{
	int		pipe_fds[2];
	pid_t	fork_pid;

	if (pipe(pipe_fds) == ERROR)
		ft_error();
	fork_pid = fork();
	if (fork_pid == ERROR)
		ft_error();
	if (fork_pid == CHILD)
		child_process(cmd, env, pipe_fds, STDIN_FILENO);
	close_fds_run_with_pipes(pipe_fds, STDIN_FILENO);
}

void	simple_command(t_cmd *cmd, t_env *env)
{
	pid_t	fork_pid;

	if (redirect_input(cmd, env, STDIN_FILENO) == ERROR)
	{
		ft_putendl_fd("Error: input redirection", STDERR_FILENO);
		g_last_pid = ERROR;
		exit(g_last_pid);
	}
	if (redirect_output(cmd, env, STDOUT_FILENO) == ERROR)
	{
		ft_putendl_fd("Error: output redirection", STDERR_FILENO);
		g_last_pid = ERROR;
		exit(g_last_pid);
	}
	if (execute_built_in_cmd(cmd, cmd->exec->cmd_args[0], env) == SUCCESS)
		return ;
	else
	{
		fork_pid = fork();
		if (fork_pid == ERROR)
			ft_error();
		if (fork_pid == CHILD)
			ft_execute(cmd, env);
	}
}

void	executor(t_cmd *cmd, t_token *tokens, t_env *env)
{
	if (!cmd)
		return ;
	if (tokens->type == PIPE)
		prepare_to_pipe_and_fork(cmd, env);
	else
		simple_command(cmd, env);
	wait_for_pids();
}
