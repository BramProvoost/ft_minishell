/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   case_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 16:57:00 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/03/09 11:19:56 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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
		last->type = HEREDOC;
		last->value = ft_strdup("<<");
		last->len = 2;
	}
	else
	{
		last->type = INPUT_SINGLE;
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
		last->type = OUTPUT_APPEND;
		last->value = ft_strdup(">>");
		last->len = 2;
	}
	else
	{
		last->type = OUTPUT_SINGLE;
		last->value = ft_strdup(">");
		last->len = 1;
	}
}

// a "b "

void	word_case(t_token **token, t_line *line)
{
	t_token	*word_token;
	char	*last_char;
	char	p;
	char	c;

	c = get_current_char(*line);
	p = get_prev_char(*line);
	if (!*token)
		add_token_back(token, create_token());
	if (p == ' ' && line->quote == '0' && line->quote_start == false)
		add_token_back(token, create_token());
	word_token = last_token(*token);
	last_char = ft_strlendump(&line->text[line->position], 1);
	word_token->type = WORD;
	word_token->value = ft_strjoin(word_token->value, last_char);
	free(last_char);
	word_token->len++;
	next_char(line);
	if (line->quote != '0' && line->quote_start == true)
		line->quote_end = false;
	else
		line->quote_end = true;
	data_to_token(token, line);
}

// void	old_word_case(t_token **token, t_line *line)
// {
// 	t_token	*word_token;
// 	char	*last_char;
// 	char	c;

// 	if (!*token)
// 		add_token_back(token, create_token());
// 	c = get_prev_char(*line);
// 	if (line->quote == 0)
// 		if (c == '\'' || c == '"')
// 			add_token_back(token, create_token());
// 	if (last_token(*token)->type != WORD)
// 		add_token_back(token, create_token());
// 	else if (line->position > 0 && line->text[line->position - 1] == ' ' && line->quote == 0)
// 		add_token_back(token, create_token());
// 	word_token = last_token(*token);
// 	last_char = ft_strlendump(&line->text[line->position], 1);
// 	word_token->type = WORD;
// 	word_token->value = ft_strjoin(word_token->value, last_char);
// 	word_token->len++;
// 	next_char(line);
// 	data_to_token(token, line);
// }
