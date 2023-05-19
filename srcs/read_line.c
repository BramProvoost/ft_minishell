/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 16:04:08 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/19 10:05:57 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_sure_line_is_empty(char **line)
{
	if (line && *line)
		*line = (char *) NULL;
}

void	add_line_in_history(char **line)
{
	if (*line && **line)
		add_history(*line);
}

void	line_reader(char **line, const char *display_name)
{
	char	*temp;

	make_sure_line_is_empty(line);
	temp = readline(display_name);
	if (!temp)
		exit(EXIT_SUCCESS);
	*line = ft_strdup(temp);
	free(temp);
	add_line_in_history(line);
}
