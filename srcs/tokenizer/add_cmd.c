/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 13:29:03 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/17 14:54:01 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_cmd	*new_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (cmd);
}

t_exec	*new_t_exec(void)
{
	t_exec	*exec;

	exec = ft_calloc(1, sizeof(t_exec));
	if (!exec)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (exec);
}

void	path_and_cmd_to_t_cmd(t_cmd *cmd, char *cmd_and_args, char **env)
{
	char	*path_and_cmd;
	char	**split_cmd_and_args;

	if (!cmd)
		cmd = new_t_cmd();
	split_cmd_and_args = ft_split(cmd_and_args, ' ');
	if (is_buld_in_cmd(split_cmd_and_args[0]))
		path_and_cmd = ft_strdup(split_cmd_and_args[0]);
	else
		path_and_cmd = get_full_cmd(split_cmd_and_args[0], get_paths(env));
	cmd->exec = new_t_exec();
	cmd->exec->exec = path_and_cmd;
	cmd->exec->args = split_cmd_and_args;
}

/*	Questions:
	how to use s_file?
	- why int heredoc if we have t_file_type?
	- use next?
*/
// void	file_to_t_cmd(t_cmd *cmd, char *file)
// {
// 	if (!cmd)
// 		cmd = new_t_cmd();
// 	cmd->file = file;
// }

void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd && cmd->next) 
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->exec->exec)
			free(temp->exec->exec);
		if (temp->exec->args)
			free_2d(temp->exec->args);
	}
}

// todo: add file stuff
void	temp_t_cmd_printer(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		i = 0;
		if (cmd->exec && cmd->exec->exec)
			printf("cmd->exec->exec = '%s'\n", cmd->exec->exec);
		if (cmd->exec && cmd->exec->args)
		{
			while (cmd->exec->args[i])
			{
				printf("cmd->exec->args[%d] = '%s'\n", i, cmd->exec->args[i]);
				i++;
			}
		}
		cmd = cmd->next;
	}
}
