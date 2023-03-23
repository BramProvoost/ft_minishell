/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_token_printer.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 14:11:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/03/23 20:12:18 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/* temporary function for visualising */
char	*temp_type_to_string(t_type type)
{
	if (type == CMD)
		return ("CMD");
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == INPUT_SINGLE)
		return ("INPUT_S");
	if (type == HEREDOC)
		return ("INPUT_D");
	if (type == OUTPUT_SINGLE)
		return ("OUTPUT_S");
	if (type == OUTPUT_APPEND)
		return ("OUTPUT_D");
	if (type == FILE_T)
		return ("FILE");
	return ("No tokens found");
}

/* temporary function for visualising */
void	temp_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf(GRAY"type: %s\tlen: %li\tvalue: \""GREEN"%s"GRAY"\"\n"NC,
			temp_type_to_string(tokens->type), tokens->len, tokens->value);
		tokens = tokens->next;
	}
}
