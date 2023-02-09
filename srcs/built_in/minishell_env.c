/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_env.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/25 16:24:14 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:27:36 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_env(t_env *env)
{
	while (env)
	{
		if (env->has_value == true)
		{
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->value, 1);
			env = env->next;
		}
	}
	return (SUCCESS);
}
