/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/09 19:32:01 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	is_exit(t_token *tokens)
{
	if (tokens && tokens->value)
		if (ft_strncmp(tokens->value, "exit", 5) == 0)
			return (1);
	return (0);
}

int	test_shell(char *line, char **envp)
{
	t_token	*tokens;

	if (!line)
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	// tokens = tokenizer("''");	// fix empty quotes
	// tokens = tokenizer(" a");	// fix spaces before first word
	
	// tokens = tokenizer("");
	// tokens = tokenizer("ls-la");
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
	temp_print_tokens(tokens);	// temp using for visualizing
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	(void)line;		// temp until using line
	(void)envp;		// temp until using envp
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	shell(char *line, char **envp)
{
	t_token	*tokens;

	if (!line)
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	delete_tokens(tokens);
	(void)envp;		// temp until using envp
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
