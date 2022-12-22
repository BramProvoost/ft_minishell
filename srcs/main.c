/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/22 18:42:10 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[], char **envp)
{
	t_token	*token;

	// token = tokenizer("ls -la");
	// token = tokenizer("echo hello > outfile");
	// token = tokenizer("<b<<|>d>>");
	token = tokenizer("||");
	// token = tokenizer("");
	print_tokens(token);
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
