/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/19 18:02:29 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	test_shell(char *line, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line || line[0] == '\0')
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	free(line);
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	replace_word_with_file(tokens);
	replace_first_word_with_cmd(tokens);
	temp_print_tokens(tokens, "Tokens");
	expander(&tokens, env);
	temp_print_tokens(tokens, "Expand Tokens");
	cmd = get_cmd_from_token(tokens, env);
	temp_t_cmd_printer(cmd, "Commands");
	executor(cmd, tokens, env);
	delete_tokens(tokens);
	delete_cmds(cmd);
	return (EXIT_SUCCESS);
}

int	shell(char *line, t_env *env)
{
	t_token	*tokens;
	t_cmd	*cmd;

	if (!line || line[0] == '\0')
		return (EXIT_FAILURE);
	tokens = tokenizer(line);
	free(line);
	if (!gramer_is_valid(tokens))
		return (EXIT_FAILURE);
	replace_word_with_file(tokens);
	replace_first_word_with_cmd(tokens);
	expander(&tokens, env);
	cmd = get_cmd_from_token(tokens, env);
	executor(cmd, tokens, env);
	delete_tokens(tokens);
	delete_cmds(cmd);
	return (EXIT_SUCCESS);
}

void	ft_exit(void)
{
	system("leaks -q minishell");
}

int	g_exit_status;

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;
	t_env		*env;

	g_exit_status = 0;
	atexit(ft_exit);
	create_env_list(&env, envp);
	init_signals();
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		test_shell(line, env);
	}
	free_env_list(&env);
	(void)argc;
	(void)argv;
	return (EXIT_SUCCESS);
}
