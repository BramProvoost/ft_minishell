/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/27 14:47:09 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	test_shell(char *line, t_env **env_double_ptr)
{
	t_token	*tokens;
	t_cmd	*cmd;
	t_env	*env;

	env = *env_double_ptr;
	if (!line || line[0] == '\0' || line[0] == ' ')
	{
		free(line);
		return (EXIT_FAILURE);
	}
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
	executor(cmd, tokens, env_double_ptr);
	delete_tokens(tokens);
	delete_cmds(cmd);
	return (EXIT_SUCCESS);
}

void	ft_exit(void)
{
	system("leaks -q minishell");
	system("lsof -c minishell");
}

int	g_exit_status;

int	main(int argc, char *argv[], char **envp)
{
	static char	*line;
	t_env		*env;

	g_exit_status = 0;
	if (argc > 1)
		return (ft_putendl_fd("minishell: too many arguments", STDERR));
	atexit(ft_exit);
	create_env_list(&env, envp);
	init_signals();
	while ("you don't close me")
	{
		line_reader(&line, "minishell$ ");
		test_shell(line, &env);
	}
	free_env_list(&env);
	(void)argv;
	return (EXIT_SUCCESS);
}
