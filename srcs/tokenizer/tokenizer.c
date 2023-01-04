/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:36:39 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/04 18:40:09 by bprovoos      ########   odam.nl         */
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

// t_type	get_type_of_token(t_line line)
// {
// 	char	c;
// 	char	n;

// 	c = get_current_char(line);
// 	n = get_next_char(line);
// 	if (c == '|')
// 		return (PIPE);
// 	if (c == '<' && n == '<')
// 		return (INPUT_D);
// 	if (c == '<')
// 		return (INPUT_S);
// 	if (c == '>' && n == '>')
// 		return (OUTPUT_D);
// 	if (c == '>')
// 		return (OUTPUT_S);
// 	return (WORD);
// }

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

char	*ft_strlendump(const char *str, size_t length)
{
	char	*temp;

	temp = (char *)malloc(sizeof(*str) * (length + 1));
	if (!temp)
		return (NULL);
	temp[length] = '\0';
	while (length > 0)
	{
		length--;
		temp[length] = str[length];
	}
	return (temp);
}

void	word_case(t_token **token, t_line line)
{
	t_token	*word_token;

	/*	check if last node is word case.
		append to word or create wordt */
	/* add only token if it is not a word case! */
	if (!*token)
		add_token_back(token, create_token());
	else if (last_token(*token)->type != WORD)
		add_token_back(token, create_token());
	word_token = last_token(*token);
	word_token->value = ft_strjoin(word_token->value, ft_strlendump(&line.text[line.position], 1));
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
		word_case(token, *line);
		next_char(line);
		data_to_token(token, line);
	}
}

t_token	*tokenizer(char *raw_line)
{
	t_line	line;
	t_token *token_lst;

	line.text = raw_line;
	line.len = ft_strlen(raw_line);
	line.position = 0;
	token_lst = NULL;
	while(line.position < line.len)
	{
		data_to_token(&token_lst, &line);
		move_position(token_lst, &line);
	}
	return (token_lst);
}
