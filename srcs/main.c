/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/16 10:13:21 by bprovoos      ########   odam.nl         */
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

t_cmd	*get_cmd_from_token(t_token *tokens, char **env)
{
	t_cmd	*cmd;
	t_args	args;
	int		first_word;
	// todo
	// check type if executeble or buldin
	// if type cmd -> malloc and add to cmd list

	cmd = NULL;
	first_word = true;
	create_env_list(&args.env, env);
	init_paths(&args);
	while (tokens)
	{
		if (tokens->type == WORD)
		{
			if (first_word)
				tokens->type = CMD;
			first_word = false;
		}
		else
			first_word = true;
		tokens = tokens->next;
	}
	(void)tokens;
	return (cmd);
}

int	test_shell(char *line, char **env)
{
	t_token	*tokens;
	t_cmd	*cmd;

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
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	cmd = get_cmd_from_token(tokens, env);
	temp_print_tokens(tokens);	// temp using for visualizing
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	// executor(cmd, tokens);
	(void)line;		// temp until using line
	(void)env;		// temp until using envp
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	shell(char *line, char **env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line)
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	cmd = get_cmd_from_token(tokens, env);
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	// executor(cmd, tokens);
	delete_tokens(tokens);
	(void)env;		// temp until using envp
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char **env)
{
	static char	*line;

	g_last_pid = 0;
	init_signals();
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		test_shell(line, env);
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
