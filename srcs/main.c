/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:42:49 by bprovoos          #+#    #+#             */
/*   Updated: 2023/03/09 09:58:19 by edawood          ###   ########.fr       */
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

char	**get_paths(t_env *env)
{
	int	i;
	char	*path;
	char	**paths;

	i = 0;
	while (env->key && env->has_value && ft_strncmp("PATH", env->key, 4))
		env = env->next;	
	if (env->key == NULL)
		error_exit(errno, "PATH not found");
	path = ft_strdup(env->value);
	paths = ft_split(path, ':');
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


void	replace_word_with_file(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->prev)
			if (tokens->prev->type != PIPE && tokens->prev->type != WORD)
				tokens->type = FILE_T;
		tokens = tokens->next;
	}
}

// void	add_to_2d(char **old, char *new_str)
// {
// 	int	i;

// 	if (!old)
// 		old = ft_calloc(2, sizeof(char));
// 	if (!old)
// 		return;
// 	i = 0;
	
// }

t_cmd	*get_cmd_from_token(t_token *tokens, t_env *env)
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
			continue;
		}
		else if (tokens->type == FILE_T)
			file_to_t_cmd(&cmd, tokens->type, tokens->value);
		tokens = tokens->next;
	}
	return (cmd);
}

int	test_shell(char *line, t_env *env)
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
	replace_word_with_file(tokens);
	replace_first_word_with_cmd(tokens);
	cmd = get_cmd_from_token(tokens, env);
	temp_print_tokens(tokens);				// temp using for visualizing
	temp_t_cmd_printer(cmd);				// temp using for visualizing
	if (is_exit(tokens))
		exit(ft_putendl_fd("exit", 1));
	executor(cmd, tokens, env);				// not using until 
	(void)line;								// temp until using line
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	shell(char *line, t_env *env)
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
	temp_print_tokens(tokens);	// temp using for visualizing
	executor(cmd, tokens, env);
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;
	t_env *env;

	g_last_pid = 0;
	create_env_list(&env, envp);
	init_signals();
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		test_shell(line, env);	// temp for printing tokens
		// shell(line, env); // use before eval
	}
	free_env_list(&env);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
