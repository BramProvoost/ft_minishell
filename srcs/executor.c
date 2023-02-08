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
