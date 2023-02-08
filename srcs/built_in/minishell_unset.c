/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:31:00 by edawood           #+#    #+#             */
/*   Updated: 2023/01/29 11:01:49 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

int	minishell_unset(t_cmd *cmd, t_args *args)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (cmd->exec->args[i])
	{
		j = 0;
		while (args->env->next)
		{
			tmp = ft_strjoin(cmd->exec->args[i], "=");
			if (!ft_strncmp(args->env->key, tmp, ft_strlen(tmp)))
			{
				free(args->env->key);
				args->env->key = ft_strdup("");
			}
			free(tmp);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
