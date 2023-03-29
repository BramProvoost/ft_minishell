/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 21:20:44 by edawood           #+#    #+#             */
/*   Updated: 2023/03/27 21:22:36 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	assign_env_value(t_env *new, char *env, int i, int len)
{
	new->key = ft_substr(env, 0, i);
	new->value = ft_substr(env, i + 1, len - i);
	new->has_value = true;
}
