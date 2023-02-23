/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/22 20:13:53 by bprovoos      ########   odam.nl         */
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

char	**get_paths(char **env)
{
	int	i;
	char	*path;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp("PATH=", env[i], 5))
		i++;
	path = ft_strdup(&env[i][5]);
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	free(path);
	return (paths);
}

void	replace_first_word_with_cmd(t_token *tokens)
{
	int		first_word;

	first_word = true;
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
}

/* todo
	How do I detect of a token (CMD?)is a file?
*/
t_cmd	*get_cmd_from_token(t_token *tokens, char **env)
{
	t_cmd	*cmd;
	char	*cmd_and_args;

	cmd = NULL;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			cmd_and_args = ft_strdup(tokens->value);
			tokens = tokens->next;
			while (tokens && tokens->type == WORD)
			{
				cmd_and_args = ft_strjoin(cmd_and_args, " ");
				cmd_and_args = ft_strjoin(cmd_and_args, tokens->value);
				tokens = tokens->next;
			}
			path_and_cmd_to_t_cmd(&cmd, cmd_and_args, env);
			free(cmd_and_args);
		}
		else
			tokens = tokens->next;
	}
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
	replace_first_word_with_cmd(tokens);
	cmd = get_cmd_from_token(tokens, env);
	temp_print_tokens(tokens);				// temp using for visualizing
	temp_t_cmd_printer(cmd);				// temp using for visualizing
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	// executor(cmd, tokens);				// not using until 
	(void)line;								// temp until using line
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
	replace_first_word_with_cmd(tokens);
	cmd = get_cmd_from_token(tokens, env);
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	// executor(cmd, tokens);
	delete_tokens(tokens);
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
		test_shell(line, env);	// temp for printing tokens
		// shell(line, env); // use before eval
	}
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
