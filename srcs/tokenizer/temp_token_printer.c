/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_token_printer.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 14:11:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/16 10:50:21 by bprovoos      ########   odam.nl         */
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

/* temporary function for visualising */
void	temp_print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("type: %s\tlen: %li\tvalue: \""GREEN"%s"NC"\"\n", temp_type_to_string(tokens->type), tokens->len, tokens->value);
		tokens = tokens->next;
	}
}
