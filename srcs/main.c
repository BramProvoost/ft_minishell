/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/08 11:42:49 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/04 15:17:46 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char *argv[], char **envp)
{
	t_token	*token;

	// token = tokenizer("ls -la");
	// token = tokenizer("echo hello > outfile");
	// token = tokenizer("<b<<|>d>>");
	// token = tokenizer("||");
	token = tokenizer("<|<<");
	print_tokens(token);
	(void)argc;
	(void)argv;
	(void)envp;
	return (0);
}

/*
Process 40557 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x00000001000019ff minishell`pipe_case(token=0x0000000100102380) at tokenizer.c:97:1
   94           token->type = PIPE;
   95           token->value = "|";
   96           token->len = 1;
-> 97   }
   98  
   99   void    input_case(t_token **token, t_line line)
   100  {
Target 0: (minishell) stopped.
(lldb) p token
(t_token *) $8 = 0x0000000100102380
(lldb) p *token
(t_token) $9 = {
  type = PIPE
  value = 0x0000000100001fa1
  len = 1
  next = 0x0000000000000000
  prev = 0x0000000000000000
}
(lldb) s
Process 40557 stopped
* thread #1, queue = 'com.apple.main-thread', stop reason = step in
    frame #0: 0x0000000100001bbe minishell`data_to_token(token=0x00007ffeefbff2b8, line=0x00007ffeefbff2c0) at tokenizer.c:143:3
   140 
   141          c = get_current_char(*line);
   142          if (c == '|')
-> 143                  pipe_case(*token);
   144          else if (c == '<')
   145                  input_case(token, *line);
   146          else if (c == '>')
Target 0: (minishell) stopped.
(lldb) p token
(t_token **) $10 = 0x00007ffeefbff2b8
(lldb) p *token
(t_token *) $11 = 0x0000000000000000
*/