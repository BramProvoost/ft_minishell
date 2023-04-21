/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   temp_token_printer.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/15 14:11:57 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/04/21 17:48:39 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

/* temporary function for visualising */
char	*temp_type_to_string(t_type type)
{
	if (type == CMD)
		return ("CMD\t");
	if (type == WORD)
		return ("WORD\t");
	if (type == PIPE)
		return ("PIPE\t");
	if (type == INPUT_SINGLE)
		return ("INPUT_SINGLE");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == OUTPUT_SINGLE)
		return ("OUTPUT_SINGLE");
	if (type == OUTPUT_APPEND)
		return ("OUTPUT_APPEND");
	if (type == FILE_T)
		return ("FILE\t");
	return ("No tokens found");
}

/* temporary function for visualising */
void	temp_print_tokens(t_token *tokens, char *header)
{
	printf(BLUE"%s"NC"\n", header);
	while (tokens)
	{
		printf(GRAY"type: %s\tlen: %li\tvalue: \""GREEN"%s"GRAY"\""NC"\n", 
			temp_type_to_string(tokens->type), tokens->len, tokens->value);
		tokens = tokens->next;
	}
	printf(BLUE"End %s"NC"\n", header);
}
