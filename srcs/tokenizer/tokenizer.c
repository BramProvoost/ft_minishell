/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:36:39 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/15 19:09:02 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_token	*new_token(t_token *last, t_type type)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	if (last)
	{
		last->next = new;
		new->prev = last;
	}
	new->type = type;
	return (new);
}

void	add_type_to_token_list(t_token *token, t_type type)
{
	while (token->next)
		token = token->next;
	if (token->type == TOKEN_EOF)
		token->type = type;
	else
		token->next = new_token(token, type);
}

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

// int	token_case(t_line line, char *chars)
// {
	
// }

// t_type	get_type_of_char(t_line *line)
// {
// 	// if (token_case(*line, " \t\n"))
// 	// {
// 	// 	next_char(line);
// 	// 	return (get_type_of_char(line));
// 	// }
// 	if (token_case(*line, "|"))
// 		return (PIPE);
// 	if (token_case(*line, "<"))
// 		return (INPUT_S);
// 	if (token_case(*line, "<<"))
// 		return (INPUT_D);
// 	if (token_case(*line, ">"))
// 		return (OUTPUT_S);
// 	if (token_case(*line, ">>"))
// 		return (OUTPUT_D);
// 	return (WORD);
// }

void	move_position(t_token *token, t_line *line)
{
	while (token->next)
		token = token->next;
	if (token->type == INPUT_D)
		line->position++;
	if (token->type == OUTPUT_D)
		line->position++;
	line->position++;
}

t_type	get_type_of_token(t_line line)
{
	char	c;
	char	n;

	c = get_current_char(line);
	n = get_next_char(line);
	if (c == '|')
		return (PIPE);
	if (c == '<' && n == '<')
		return (INPUT_D);
	if (c == '<')
		return (INPUT_S);
	if (c == '>' && n == '>')
		return (OUTPUT_D);
	if (c == '>')
		return (OUTPUT_S);
	return (WORD);
}

t_token	*tokenizer(char *raw_line)
{
	t_line	line;
	t_token *token;
	t_type	type;

	line.text = raw_line;
	line.len = ft_strlen(raw_line);
	line.position = 0;
	token = new_token(NULL, TOKEN_EOF);
	while(line.position < line.len)
	{
		type = get_type_of_token(line);
		add_type_to_token_list(token, type);
		move_position(token, &line);
	}
	add_type_to_token_list(token, TOKEN_EOF);
	return (token);
}
