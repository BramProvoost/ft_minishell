/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/27 09:39:09 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	shell(char *line, char **envp)
{
	t_token	*token;

	// token = tokenizer("");
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
	print_tokens(token);	// temp using for visualizing
	(void)line;		// temp until using line
	(void)envp;		// temp until using envp
	delete_tokens(token);
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
