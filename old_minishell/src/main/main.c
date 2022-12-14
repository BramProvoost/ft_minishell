/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 14:36:20 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/02 11:02:27 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	shell(char *line, char **envp)
{
	parser(line);
	(void)envp;		// temp until using envp
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;

	if (input_is_argv(argc, argv, &line))
		return (shell(line, envp));
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		shell(line, envp);
	}
	return (0);
}
