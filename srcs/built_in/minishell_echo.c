/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 21:22:53 by edawood           #+#    #+#             */
/*   Updated: 2023/01/25 16:43:50 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

int	minishell_echo(char *arg, t_cmd *cmd)
{
	int		i;
	int		j;
	bool	n_flag;

	i = 1;
	n_flag = false;
	if (!arg)
		return (ERROR);
	while (cmd->exec->args[i])
	{
		j = 0;
		if (cmd->exec->args[i][j] == '-')
		{
			j++;
			while (cmd->exec->args[i][j] == 'n')
			{
				n_flag = true;
				j++;
			}
		}
		else
			fprintf(stderr, "%s", cmd->exec->args[i]);
		if (n_flag == false)
			ft_putendl_fd("", 1);
		i++;
	}
	return (SUCCESS);
}
