/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/19 16:34:48 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/19 16:35:13 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	replace_first_word_with_cmd(t_token *tokens)
{
	int		first_word;

	first_word = true;
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			if (first_word)
				tokens->type = CMD;
			first_word = false;
		}
		else if (tokens->type == PIPE)
			first_word = true;
		tokens = tokens->next;
	}
}

int	is_rederect(t_type type)
{
	if (type == INPUT_SINGLE)
		return (1);
	if (type == HEREDOC)
		return (1);
	if (type == OUTPUT_SINGLE)
		return (1);
	if (type == OUTPUT_APPEND)
		return (1);
	return (0);
}

void	replace_word_with_file(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->prev)
			if (tokens->prev->type != PIPE
				&& tokens->prev->type != WORD
				&& tokens->prev->type != FILE_T
				&& !is_rederect(tokens->type))
				tokens->type = FILE_T;
		tokens = tokens->next;
	}
}
