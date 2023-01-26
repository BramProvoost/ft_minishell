/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/26 15:32:45 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	make_sure_line_is_empty(char **line)
{
	if (*line)
	{
		free (*line);
		*line = (char *) NULL;
	}
}

void	add_line_in_history(char **line)
{
	if (*line && **line)
		add_history(*line);
}

void	line_reader(char **line, const char *display_name)
{
	make_sure_line_is_empty(line);
	*line = readline(display_name);
	if (!line)
		exit(EXIT_SUCCESS);
	add_line_in_history(line);
}

int	shell(char *line, char **envp)
{
	t_token	*token;

	// token = tokenizer("ls -la");
	// token = tokenizer("ls -la");
	// token = tokenizer("echo      hello  world>outfile");
	// token = tokenizer("echo hello > world > outfile");
	// token = tokenizer("echo'hello > world'>outfile");
	// token = tokenizer("echo 'hello > world' > outfile");
	// token = tokenizer("echo  'hello > world'  >  outfile");
	// token = tokenizer("echo \"hello > world\" > outfile");
	// token = tokenizer("<b<<|>d>>");
	// token = tokenizer(" < b << | > d >> ");
	// token = tokenizer("||");
	// token = tokenizer("<|<<");
	// token = tokenizer("'ab'cd'ef'gh'ij'kl");
	// token = tokenizer("'ab\"cd'ef'gh\"ij'kl");
	// token = tokenizer(" 'ab'cd'ef'g");
	// token = tokenizer("z'ab'cd'ef'g");

	token = tokenizer(line);
	// printf("readline: %s\n", line);
	print_tokens(token);
	delete_tokens(token);
	(void)line;
	(void)envp;		// temp until using envp
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;

	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		shell(line, envp);
	}
	(void)argc;
	(void)argv;
	return (0);
}
