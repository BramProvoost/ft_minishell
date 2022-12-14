/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:36:39 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/14 14:59:33 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	add_token(t_token **token, char c)
{
	t_token	*new_token;

	new_token = malloc(sizeof(token));
	if (!token)
		exit(1);	// replace this with an error msg
	if (!*token)
	{
		*token = new_token;
		(*token)->next = NULL;
		(*token)->prev = NULL;
	}
	else 
	{
		;
	}
	(void)c;
	printf("%c", c);;
}

t_token	*tokenizer(char *raw_line)
{
	t_line	line;

	line.text = raw_line;
	line.len = 
	return (token);
}
