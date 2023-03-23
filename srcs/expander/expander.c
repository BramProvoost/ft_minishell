/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/17 10:03:55 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/03/17 12:51:57 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_token	*rm_quotes(t_token *tokens)
{
	return (tokens);
}

expander(t_token **tokens, t_env *env)
{
	while (*tokens)
	{
		if (ft_strstr((*tokens)->value, "$") != NULL)
			ft_putchar_fd(ft_strstr((*tokens)->value, "$"), 1);
		*tokens = (*tokens)->next;
	}
	(void)env;
}
