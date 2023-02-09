/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_functions.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 16:51:25 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/03 10:58:23 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	next_char(t_line *line)
{
	line->position++;
}

char	get_next_char(t_line line)
{
	if (line.position + 1 < line.len)
		return (line.text[line.position + 1]);
	return ('\0');
}

char	get_current_char(t_line line)
{
	if (line.position < line.len)
		return (line.text[line.position]);
	return ('\0');
}

char	get_prev_char(t_line line)
{
	if (line.position > 0)
		return (line.text[line.position - 1]);
	return ('\0');
}

void	move_position(t_token *token_lst, t_line *line)
{
	token_lst = last_token(token_lst);
	line->position += token_lst->len;
}
