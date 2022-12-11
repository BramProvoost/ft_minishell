#include "../executor.h"

void	executor(t_cmd *cmd, t_args *args)
{
    args->paths = init_paths(cmd->cmd, args->env);
}

int	main(void)
{
	t_args args;
	t_cmd cmd;

	executor(&cmd, &args);
	return (0);
}

// static t_fork	*new_fork(t_fork *forks)
// {
// 	t_fork	*new_fork;

// 	new_fork = (t_fork *)malloc(sizeof(t_fork));
// 	ft_check_malloc(new_fork, "new_fork");
// 	new_fork->next = NULL;
// 	if (!forks)
// 		forks = new_fork;
// 	else
// 	{
// 		forks->next = new_fork;
// 		forks = forks->next;
// 	}
// 	return (forks);
// }

// static void	waitpid_fork(t_fork *forks, t_mini_vars *vars)
// {
// 	int		status;
// 	t_fork	*next;

// 	while (forks)
// 	{
// 		if (waitpid(forks->pid, &status, 0) < 0)
// 			exit_error(errno, "waitpid_fork", NULL);
// 		next = forks->next;
// 		free(forks);
// 		forks = next;
// 	}
// 	if (WIFEXITED(status))
// 		vars->last_pid = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		vars->last_pid = WTERMSIG(status) + 128;
// }

// static void	forked_cmd(t_fork **head, t_cmd *cmd, t_mini_vars *vars)
// {
// 	t_fork	*forks;
// 	int		fd;
// 	bool	first_cmd;

// 	forks = NULL;
// 	fd = 0;
// 	first_cmd = true;
// 	while (cmd)
// 	{
// 		forks = new_fork(forks);
// 		if (first_cmd)
// 		{
// 			*head = forks;
// 			first_cmd = false;
// 		}
// 		fd = exec_forked_cmd(forks, cmd, vars, fd);
// 		cmd = cmd->next;
// 	}
// 	close(fd);
// }

// static t_fork	*simple_cmd(t_cmd *cmd, t_mini_vars *vars)
// {
// 	t_fork	*forks;

// 	if (is_special_builtin(cmd->exec->cmd))
// 	{
// 		if (redirect_input(cmd->input, STDIN_FILENO, vars))
// 			return (NULL);
// 		if (redirect_output(cmd->output, STDOUT_FILENO, vars))
// 			return (NULL);
// 		built_in(cmd, cmd->exec->cmd, vars);
// 		return (NULL);
// 	}
// 	forks = new_fork(NULL);
// 	forks->pid = fork();
// 	if (forks->pid < 0)
// 		exit_error(errno, "simple_cmd", NULL);
// 	else if (forks->pid == CHILD)
// 	{
// 		if (redirect_input(cmd->input, STDIN_FILENO, vars))
// 			exit(vars->last_pid);
// 		if (redirect_output(cmd->output, STDOUT_FILENO, vars))
// 			exit(vars->last_pid);
// 		execute_cmd(cmd, cmd->exec, vars);
// 	}
// 	return (forks);
// }

// void	executor(t_cmd *cmd, t_mini_vars *vars)
// {
// 	vars->paths = init_paths(vars->env);
// 	if (!cmd->next)
// 		forks = simple_cmd(cmd, vars);
// 	else
// 		forked_cmd(&forks, cmd, vars);
// 	if (forks)
// 		waitpid_fork(forks, vars);
// 	ft_free_char_array(vars->paths);
// }