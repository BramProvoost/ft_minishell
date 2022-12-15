/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_printer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 14:11:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/15 14:24:24 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

char	*type_to_string(t_type type)
{
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
	if (type == TOKEN_EOF)
		return ("TOKEN_EOF");
	return ("No token found");
}

void	print_tokens(t_token *token)
{
	while (token->prev)
		token = token->prev;
	while (token->next != NULL)
	{
		printf("type: %s\ttext: %s\n", type_to_string(token->type), token->text);
		token = token->next;
	}
	printf("type: %s\ttext: %s\n", type_to_string(token->type), token->text);
}
