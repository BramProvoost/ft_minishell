/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:36:39 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/25 18:43:21 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	delete_tokens(t_token *head)
{
	t_token	*temp;

	while (head->next != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

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
	t_token	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = last_token(*lst);
		last->next = new;
		new->prev = last;
	}
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

void	pipe_case(t_token **token)
{
	t_token	*last;

	add_token_back(token, create_token());
	last = last_token(*token);
	last->type = PIPE;
	last->value = ft_strdup("|");
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
		last->value = ft_strdup("<<");
		last->len = 2;
	}
	else
	{
		last->type = INPUT_S;
		last->value = ft_strdup("<");
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
		last->value = ft_strdup(">>");
		last->len = 2;
	}
	else
	{
		last->type = OUTPUT_S;
		last->value = ft_strdup(">");
		last->len = 1;
	}
}

void	word_case(t_token **token, t_line *line)
{
	t_token	*word_token;
	char	*last_char;

	if (!*token)
		add_token_back(token, create_token());
	if (last_token(*token)->type != WORD)
		add_token_back(token, create_token());
	else if (line->position > 0 && line->text[line->position - 1] == ' ' && line->quote == 0)
		add_token_back(token, create_token());
	word_token = last_token(*token);
	last_char = ft_strlendump(&line->text[line->position], 1);
	word_token->type = WORD;
	word_token->value = ft_strjoin(word_token->value, last_char);
	word_token->len++;
	next_char(line);
	data_to_token(token, line);
}

void	space_case(t_token **token, t_line *line)
{
	next_char(line);
	data_to_token(token, line);
}

void	quote_case(t_token **token, t_line *line)
{
	char	c;

	c = get_current_char(*line);
	if (c == line->quote)
		line->quote = 0;
	else
	{
		line->quote = c;
		add_token_back(token, create_token());
	}
}

void	data_to_token(t_token **token, t_line *line)
{
	char	c;

	c = get_current_char(*line);
	if (c == '\'' || c == '"')
		quote_case(token, line);
	if (line->quote == 0)
	{
		if (c == ' ')
			space_case(token, line);
		else if (c == '|')
			pipe_case(token);
		else if (c == '<')
			input_case(token, *line);
		else if (c == '>')
			output_case(token, *line);
		else if (c != '\0')
			word_case(token, line);
	}
	else if (c != '\0')
		word_case(token, line);
}

t_token	*tokenizer(char *raw_line)
{
	t_line	line;
	t_token *token_lst;

	line.text = raw_line;
	line.len = ft_strlen(raw_line);
	line.position = 0;
	line.quote = 0;
	token_lst = NULL;
	while(line.position < line.len)
	{
		data_to_token(&token_lst, &line);
		move_position(token_lst, &line);
	}
	return (token_lst);
}
