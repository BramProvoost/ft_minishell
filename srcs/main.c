/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/26 14:06:24 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[], char **envp)
{
	t_token	*token;

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

	/* geen 2 lege tokens voor de ' maken.
	na een ' een verder gaan met een nieuwe token.
	*/
	
	// token = tokenizer("'ab'cd'ef'gh'ij'kl");
	token = tokenizer("'ab\"cd'ef'gh\"ij'kl");
	// token = tokenizer(" 'ab'cd'ef'g");
	// token = tokenizer("z'ab'cd'ef'g");
	print_tokens(token);
	delete_tokens(token);
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}
