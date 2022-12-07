/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:28:56 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/02 11:55:06 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		loop_until_next_quote(char *line)
{
	char	quote;
	int		line_lenght;

	quote = line[0];
	line_lenght = 1;
	while (line[line_lenght] && line[line_lenght] != quote)
		line_lenght++;
	return (line_lenght);
}

void	add_word_desc(t_word_desc *word_desc, char *line, int pos, int flag)
{
	word_desc->word = ft_calloc(pos + 1, sizeof(char *));
	word_desc->word = ft_substr(line, 0, pos);
	word_desc->flags = flag;
}

int	get_next_word_form_line(char *line, t_word_desc *word_desc)
{
	int		line_position;

	line_position = 0;
	if (ft_strchr("'\"", line[line_position]) != NULL)
		line_position += loop_until_next_quote(line);
	else
	{
		if (ft_strchr(METACHARACTER, line[line_position]) != NULL)
		{
			line_position++;
			add_word_desc(word_desc, line, line_position, 1);
			return (line_position);
		}
		while (ft_strchr(METACHARACTER, line[line_position]) == NULL)
			line_position++;
	}
	add_word_desc(word_desc, line, line_position, 0);
	return (line_position);
}

t_world_list	*parser(char *line)
{
	int				line_length;
	t_world_list	*word_list;
	t_word_desc		*word_desc;

	line_length = 0;
	word_list = NULL;
	ft_putchar_fd('\n', 1);
	while (line[line_length])
	{
		word_desc = malloc(sizeof(t_word_desc));
		line_length += get_next_word_form_line(&line[line_length], word_desc);
		ft_putstr_fd("'", 1);
		ft_putstr_fd(word_desc->word, 1);
		ft_putstr_fd("' ", 1);
		ft_putnbr_fd(word_desc->flags, 1);
		ft_putstr_fd("'\n", 1);
		free(word_desc);
	}
	ft_putchar_fd('\n', 1);
	return (word_list);
}
