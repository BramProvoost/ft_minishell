/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:07:04 by edawood           #+#    #+#             */
/*   Updated: 2023/01/26 19:26:09 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"

void prepare_to_pipe_and_fork(t_cmd *cmd, t_args *args)
{
	int		pipe_fds[2];
	pid_t	fork_pid;
	if (pipe(pipe_fds) == ERROR)
		ft_error();
	fork_pid = fork();
	if (fork_pid == ERROR)
		ft_error();
	if (fork_pid == CHILD)
		child_process(cmd, args, pipe_fds, STDIN_FILENO);
	close_fds_run_with_pipes(pipe_fds, STDIN_FILENO);
}

void	simple_command(t_cmd *cmd, t_args *args)
{
	pid_t fork_pid;

	if (redirect_input(args, cmd->file, STDIN_FILENO) == ERROR)
	{
		ft_putendl_fd("Error: input redirection", STDERR_FILENO);
		args->status_code = ERROR;
		exit(args->status_code);
	}
	if (redirect_output(args, cmd->file, STDOUT_FILENO) == ERROR)
	{
		ft_putendl_fd("Error: output redirection", STDERR_FILENO);
		args->status_code = ERROR;
		exit(args->status_code);
	}
	if (is_built_in_cmd(cmd, cmd->exec->args[0], args) == SUCCESS)
	{
		free(cmd->exec->args);
		exit(args->status_code);
	}
	else
	{
		fork_pid = fork();
		if (fork_pid == ERROR)
			ft_error();
		if (fork_pid == CHILD)
			ft_execute(cmd, args);	
	}
}

void	executor(t_cmd *cmd, t_args *args)
{
	if (!cmd->arg)
		return ;
	args->paths = init_paths(args);
	if (!cmd->next)
		simple_command(cmd, args);
	// else
	// 	prepare_to_pipe_and_fork(cmd, args);
	// wait_for_pids(args);
}

int	main(int argc, char **argv, char **env)
{
	t_args args;
	t_cmd cmd;
	
	if (argc != 3)
	{
		ft_putendl_fd("Error: wrong number of args", 2);
		exit(1);
	}
	cmd.file = (t_file *)malloc(sizeof(t_file));
	cmd.exec = (t_exec *)malloc(sizeof(t_exec));
	cmd.file->file_name = ft_strdup(argv[1]);
	cmd.file->type = INPUT_SINGLE;
	cmd.arg = ft_strdup(argv[2]);
	cmd.exec->args = ft_split(cmd.arg, ' ');
	cmd.next = NULL;
	// cmd.arg = argv[3];
	// cmd.file = cmd.file->next;
	// cmd.file->file_name = argv[4];
	// cmd.file->type = OUTPUT;
	// copy_env(&args, env);
	create_env_list(&args.env, env);
	free_env_list(&args.env);
	// executor(&cmd, &args);
	free(cmd.file->file_name);
	free(cmd.file);
	free_2d(cmd.exec->args);
	free(cmd.arg);
	// free_2d(args.paths);
	system("leaks minishell");
	return (0);
}
