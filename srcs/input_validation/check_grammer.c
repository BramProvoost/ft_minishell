/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_grammer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/27 09:49:34 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/01 17:45:44 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	print_grammer_error(int type)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token \'", STDERR_FILENO);
	if (type == PIPE)
		ft_putstr_fd("|", STDERR_FILENO);
	else if (type == OUTPUT_S)
		ft_putstr_fd(">", STDERR_FILENO);
	else if (type == OUTPUT_D)
		ft_putstr_fd(">>", STDERR_FILENO);
	else if (type == INPUT_S)
		ft_putstr_fd("<", STDERR_FILENO);
	else if (type == INPUT_D)
		ft_putstr_fd("<<", STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	g_last_pid = 258;
	return (0);
}

int	gramer_is_valid(t_token *tokens)
{
	t_type	last_type;

	last_type = WORD;
	while (tokens)
	{
		if (!tokens->next && tokens->type != WORD)
			return (print_grammer_error(tokens->type));
		if (tokens->type == PIPE && (!tokens->prev || last_type != WORD))
			return (print_grammer_error(PIPE));
		last_type = tokens->type;
		tokens = tokens->next;
	}
	return (1);
}