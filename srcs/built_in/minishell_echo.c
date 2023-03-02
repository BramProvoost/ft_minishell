/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_echo.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 21:22:53 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/22 20:04:02 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_echo(char *arg, t_cmd *cmd)
{
	int		i;
	int		j;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (!arg)
		return (ERROR);
	while (cmd->exec->cmd_args[i])
	{
		j = 0;
		if (cmd->exec->cmd_args[i][j] == '-')
		{
			j++;
			while (cmd->exec->cmd_args[i][j] == 'n')
			{
				n_flag = true;
				j++;
			}
		}
		if (n_flag == false)
			ft_putendl_fd("", 1);
		i++;
	}
	return (SUCCESS);
}
