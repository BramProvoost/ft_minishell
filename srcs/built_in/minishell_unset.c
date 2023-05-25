/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:31:00 by edawood           #+#    #+#             */
/*   Updated: 2023/05/25 19:37:10 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	free_list(t_cmd *cmd, t_env **env, int i)
{
	t_env	*current;
	t_env	*previous;

	previous = NULL;
	current = *env;
	while (current != NULL)
	{
		if (!ft_strncmp(current->key, cmd->exec->cmd_args[i], \
			ft_strlen(current->key)))
		{
			if (previous == NULL)
				*env = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
}

int	minishell_unset(t_cmd *cmd, t_env **env)
{
	int		i;

	i = 1;
	while (cmd->exec->cmd_args[i])
	{
		free_list(cmd, env, i);
		i++;
	}
	return (SUCCESS);
}
