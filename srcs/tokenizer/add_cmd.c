/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/02/17 13:29:03 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/04/21 10:51:29 by bprovoos      ########   odam.nl         */
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

void	add_t_cmd_back(t_cmd *cmd)
{
	if (!cmd)
	{
		cmd = new_t_cmd();
	}
	else
	{
		while ((cmd)->next)
			cmd = (cmd)->next;
		(cmd)->next = new_t_cmd();	
	}
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

t_file	*new_t_file(void)
{
	t_file	*type;

	type = ft_calloc(1, sizeof(t_file));
	if (!type)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (type);
}

void	path_and_cmd_to_t_cmd(t_cmd **cmd, char **split_cmd_and_args, t_env *env)
{
	t_cmd	*tmp;
	char	*path_and_cmd;

	if (!*cmd)
		*cmd = new_t_cmd();
	else
		add_t_cmd_back(*cmd);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	if (is_buld_in_cmd(split_cmd_and_args[0]))
		path_and_cmd = ft_strdup(split_cmd_and_args[0]);
	else
		path_and_cmd = get_full_cmd(split_cmd_and_args[0], get_paths(env));
	tmp->exec = new_t_exec();
	tmp->exec->cmd_path = path_and_cmd;
	tmp->exec->cmd_args = split_cmd_and_args;
}

void	file_to_t_cmd(t_cmd **cmd, t_type type, char *file)
{
	t_cmd	*tmp;
	if (!*cmd)
		*cmd = new_t_cmd();
	else
		add_t_cmd_back(*cmd);
	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->file = new_t_file();
	tmp->file->type = type;
	tmp->file->file_name = file;
}

void	free_t_cmd(t_cmd *cmd)
{
	t_cmd	*temp;

	while (cmd && cmd->next) 
	{
		temp = cmd;
		cmd = cmd->next;
		if (temp->exec->cmd_path)
			free(temp->exec->cmd_path);
		if (temp->exec->cmd_args)
			free_2d(temp->exec->cmd_args);
		free(temp->exec);
		free(temp->file);
		free(temp);
	}
}

void	temp_t_cmd_printer(t_cmd *cmd, char *header)
{
	int	i;
	int	j;

	i = 0;
	printf(BLUE"%s\n"NC, header);
	while (cmd)
	{
		j = 0;
		if (cmd->exec)
		{
			if (cmd->exec->cmd_path)
				printf(GRAY"cmd[%d]->exec->cmd_path = '"GREEN"%s"GRAY"'"NC"\n", i, cmd->exec->cmd_path);
			if (cmd->exec->cmd_args)
			{
				while (cmd->exec->cmd_args[j])
				{
					printf(GRAY"cmd[%d]->exec->cmd_args[%d] = '"GREEN"%s"GRAY"'"NC"\n", i, j, cmd->exec->cmd_args[j]);
					j++;
				}
			}
		}
		if (cmd->file)
		{
			printf(GRAY"cmd[%d]->file->type = '"GREEN"%s"GRAY"'"NC"\n",i, temp_type_to_string(cmd->file->type));
			printf(GRAY"cmd[%d]->file->file_name = '"GREEN"%s"GRAY"'"NC"\n", i, cmd->file->file_name);
		}
		cmd = cmd->next;
		i++;
	}
	printf(BLUE"End %s"NC"\n", header);
}
