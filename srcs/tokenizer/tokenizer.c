/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:36:39 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/17 13:10:29 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	space_case(t_token **token, t_line *line)
{
	next_char(line);
	data_to_token(token, line);
}

void	quote_case(t_line *line)
{
	char	c;

	c = get_current_char(*line);
	if (c == line->quote)
		line->quote = 0;
	else if (line->quote == 0)
		line->quote = c;
}

void	data_to_token(t_token **token, t_line *line)
{
	char	c;

	c = get_current_char(*line);
	if (line->quote == 0)
	{
		if (c == ' ')
			space_case(token, line);
		else if (c == '|')
			pipe_case(token);
		else if (c == '<')
			input_case(token, line);
		else if (c == '>')
			output_case(token, line);
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

	line.text = ft_strdup(raw_line);
	line.len = ft_strlen(raw_line);
	line.position = 0;
	line.quote = 0;
	token_lst = NULL;
	while(line.position < line.len)
	{
		data_to_token(&token_lst, &line);
		move_position(token_lst, &line);
	}
	free(line.text);
	return (token_lst);
}
