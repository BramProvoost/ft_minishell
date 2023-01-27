/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_printer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 14:11:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/27 11:19:15 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*type_to_string(t_type type)
{
	if (type == CMD)
		return ("CMD");
	if (type == WORD)
		return ("WORD");
	if (type == PIPE)
		return ("PIPE");
	if (type == INPUT_S)
		return ("INPUT_S");
	if (type == INPUT_D)
		return ("INPUT_D");
	if (type == OUTPUT_S)
		return ("OUTPUT_S");
	if (type == OUTPUT_D)
		return ("OUTPUT_D");
	return ("No tokens found");
}

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type: %s\tlen: %li\ttext: \""GREEN"%s"NC"\"\n", type_to_string(tokens->type), tokens->len, tokens->value);
		tokens = tokens->next;
	}
}
