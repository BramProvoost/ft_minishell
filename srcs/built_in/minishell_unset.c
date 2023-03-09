/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:31:00 by edawood           #+#    #+#             */
/*   Updated: 2023/03/09 09:46:42 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_unset(t_cmd *cmd, t_env *env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (cmd->exec->cmd_args[i])
	{
		j = 0;
		while (env->next)
		{
			tmp = ft_strjoin(cmd->exec->cmd_args[i], "=");
			if (!ft_strncmp(env->key, tmp, ft_strlen(tmp)))
			{
				free(env->key);
				env->key = ft_strdup("");
			}
			free(tmp);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
