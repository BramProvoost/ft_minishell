/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/18 16:46:56 by bprovoos      ########   odam.nl         */
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
	int		i;
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
		else if (tokens->type == PIPE)
			first_word = true;
		tokens = tokens->next;
	}
}

int	is_rederect(t_type type)
{
	if (type == INPUT_SINGLE)
		return (1);
	if (type == HEREDOC)
		return (1);
	if (type == OUTPUT_SINGLE)
		return (1);
	if (type == OUTPUT_APPEND)
		return (1);
	return (0);
}

void	replace_word_with_file(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->prev)
			if (tokens->prev->type != PIPE
				&& tokens->prev->type != WORD
				&& tokens->prev->type != FILE_T
				&& !is_rederect(tokens->type))
				tokens->type = FILE_T;
		tokens = tokens->next;
	}
}

char	**add_to_2d(char **old_arr, char *new_str)
{
	int		i;
	char	**new_arr;

	i = 0;
	if (!old_arr)
	{
		new_arr = (char **)malloc(2 * sizeof(char *));
		new_arr[0] = ft_strdup(new_str);
		new_arr[1] = NULL;
		return (new_arr);
	}
	while (old_arr[i])
		i++;
	new_arr = (char **)malloc((i + 2) * sizeof(char *));
	i = 0;
	while (old_arr[i])
	{
		new_arr[i] = ft_strdup(old_arr[i]);
		i++;
	}
	new_arr[i] = ft_strdup(new_str);
	new_arr[i + 1] = NULL;
	free_2d(old_arr);
	return (new_arr);
}

t_cmd	*get_cmd_from_token(t_token *tokens, t_env *env)
{
	t_cmd	*cmd;
	char	**cmd_and_args;

	cmd = NULL;
	cmd_and_args = NULL;
	while (tokens)
	{
		if (tokens->type == CMD && tokens->value)
			cmd_and_args = add_to_2d(cmd_and_args, tokens->value);
		else if (tokens->type == WORD && tokens->value)
			cmd_and_args = add_to_2d(cmd_and_args, tokens->value);
		else if (tokens->type == FILE_T)
			file_to_t_cmd(&cmd, tokens);
		else if ((is_rederect(tokens->type) || tokens->type == PIPE) && cmd_and_args)
		{
			path_and_cmd_to_t_cmd(&cmd, cmd_and_args, env);
			free_2d(cmd_and_args);
			cmd_and_args = NULL;
		}
		tokens = tokens->next;
	}
	if (cmd_and_args)
		path_and_cmd_to_t_cmd(&cmd, cmd_and_args, env);
	free_2d(cmd_and_args);
	return (cmd);
}

int	test_shell(char *line, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line || line[0] == '\0')
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	replace_word_with_file(tokens);
	replace_first_word_with_cmd(tokens);
	temp_print_tokens(tokens, "Tokens");	// temp using for visualizing
	expander(&tokens, env);
	temp_print_tokens(tokens, "Expand Tokens");	// temp using for visualizing
	cmd = get_cmd_from_token(tokens, env);
	temp_t_cmd_printer(cmd, "Commands");	// temp using for visualizing
	executor(cmd, tokens, env);
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	shell(char *line, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line || line[0] == '\0')
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	replace_word_with_file(tokens);
	replace_first_word_with_cmd(tokens);
	cmd = get_cmd_from_token(tokens, env);
	executor(cmd, tokens, env);
	delete_tokens(tokens);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;
	t_env		*env;

	g_exit_status = 0;
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
