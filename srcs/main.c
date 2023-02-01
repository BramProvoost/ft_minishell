/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/01 17:51:57 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	shell(char *line, char **envp)
{
	t_token	*tokens;

	// tokens = tokenizer("");
	// tokens = tokenizer("ls -la");
	// tokens = tokenizer("ls -la");
	// tokens = tokenizer("echo      hello  world>outfile");
	// tokens = tokenizer("echo hello > world > outfile");
	// tokens = tokenizer("echo'hello > world'>outfile");
	// tokens = tokenizer("echo 'hello > world' > outfile");
	// tokens = tokenizer("echo  'hello > world'  >  outfile");
	// tokens = tokenizer("echo \"hello > world\" > outfile");
	// tokens = tokenizer("<b<<|>d>>");
	// tokens = tokenizer(" < b << | > d >> ");
	// tokens = tokenizer("||");
	// tokens = tokenizer("<|<<");
	// tokens = tokenizer("'ab'cd'ef'gh'ij'kl");
	// tokens = tokenizer("'ab\"cd'ef'gh\"ij'kl");
	// tokens = tokenizer(" 'ab'cd'ef'g");
	// tokens = tokenizer("z'ab'cd'ef'g");

	tokens = tokenizer(line);
	print_tokens(tokens);	// temp using for visualizing
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	(void)line;		// temp until using line
	(void)envp;		// temp until using envp
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;

	g_last_pid = 0;
	init_signals();
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		shell(line, envp);
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
