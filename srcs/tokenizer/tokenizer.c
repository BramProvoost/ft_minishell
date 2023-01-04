/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:36:39 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/04 15:17:04 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_token *create_token(void)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (new);
}

t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (create_token());
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_token_back(t_token **lst, t_token *new)
{
	if (!*lst)
		*lst = new;
	else
		last_token(*lst)->next = new;
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

void	move_position(t_token *token_lst, t_line *line)
{
	token_lst = last_token(token_lst);
	line->position += token_lst->len;
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

void	pipe_case(t_token **token)
{
	t_token	*last;

	add_token_back(token, create_token());
	last = last_token(*token);
	last->type = PIPE;
	last->value = "|";
	last->len = 1;
}

void	input_case(t_token **token, t_line line)
{
	t_token	*last;
	char	n;

	n = get_next_char(line);
	add_token_back(token, create_token());
	last = last_token(*token);
	if (n == '<')
	{
		last->type = INPUT_D;
		last->value = "<<";
		last->len = 2;
	}
	else
	{
		last->type = INPUT_S;
		last->value = "<";
		last->len = 1;
	}
}

void	output_case(t_token **token, t_line line)
{
	t_token	*last;
	char	n;

	n = get_next_char(line);
	add_token_back(token, create_token());
	last = last_token(*token);
	if (n == '>')
	{
		last->type = OUTPUT_D;
		last->value = ">>";
		last->len = 2;
	}
	else
	{
		last->type = OUTPUT_S;
		last->value = ">";
		last->len = 1;
	}
}

void	data_to_token(t_token **token, t_line *line)
{
	char	c;

	c = get_current_char(*line);
	if (c == '|')
		pipe_case(token);
	else if (c == '<')
		input_case(token, *line);
	else if (c == '>')
		output_case(token, *line);
	else if (c != '\0')
	{
		next_char(line);
		data_to_token(token, line);
	}
}

/*
Do not create a new token before you need it.
or
Create and Remove token if you don't need it.
*/

t_token	*tokenizer(char *raw_line)
{
	t_line	line;
	t_token *token_lst;

	line.text = raw_line;
	line.len = ft_strlen(raw_line);
	line.position = 0;
	token_lst = NULL;

	// token_lst = create_token();
	
	while(line.position < line.len)
	{
		// add_token_back(token_lst, create_token());
		data_to_token(&token_lst, &line);
		move_position(token_lst, &line);
	}
	
	/* overwrite last token */
	// last_token(token_lst)->type = CMD;
	// last_token(token_lst)->value = "ls -la";
	return (token_lst);
}
