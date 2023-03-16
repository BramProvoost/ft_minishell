/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   case_handler.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 16:57:00 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/03/16 17:49:56 by bprovoos      ########   odam.nl         */
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

void	word_case(t_token **token, t_line *line)
{
	t_token	*word_token;
	char	*last_char;
	char	c;

	if (!*token)
		add_token_back(token, create_token());
	c = get_current_char(*line);
	word_token = last_token(*token);
	last_char = ft_strlendump(&line->text[line->position], 1);
	word_token->type = WORD;
	word_token->value = ft_strjoin(word_token->value, last_char);
	word_token->len++;
	if (c == '\'' || c == '"')
		quote_case(line);
	next_char(line);
	if (line->quote == 0)
		data_to_token(token, line);
	else
		word_case(token, line);
}
