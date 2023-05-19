/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 20:56:52 by edawood           #+#    #+#             */
/*   Updated: 2023/05/19 15:57:42 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

bool	has_pipe(t_cmd *cmd)
{
	if (cmd->next == NULL)
		return (false);
	return (true);
}

void	close_pipes(int pipe_fds[2])
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

void	set_cmd_to_next(t_exec_data *exec_data)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = exec_data->cmd;
	exec_data->cmd = tmp_cmd->next;
}

void	exec_data_init(t_exec_data *exec_data, t_cmd *cmd, \
						t_token *tokens, t_env *env)
{
	exec_data->cmd = cmd;
	exec_data->tokens = tokens;
	exec_data->env = env;
	exec_data->is_pipe = has_pipe(cmd);
	exec_data->is_heredoc = false;
	exec_data->has_heredoc = has_heredoc(cmd);
	
}

int	redirect_in_simple_cmd(t_exec_data *exec_data)
{
	if (redirect_input(exec_data, STDIN_FILENO) == ERROR)
		return (ERROR);
	if (redirect_output(exec_data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
