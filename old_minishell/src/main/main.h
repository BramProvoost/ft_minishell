/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 09:55:42 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/05 11:02:56 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/* sources
bash manual:
https://www.gnu.org/software/bash/manual/
bash flow
http://www.aosabook.org/en/bash.html
Example:
https://github.com/vportens/minishell

Example:
https://github.com/nickdotht/minishell
Example:
https://github.com/yabtaour/Minishell-42
tutorial
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
explanation shell:
https://cs61.seas.harvard.edu/site/2019/Section7/
Shell Command Language:
https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html
BNF:
https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form

bash parser"
https://mywiki.wooledge.org/BashParser
tokenizer:
https://ix-56h.github.io/how-to-make-a-tokenizer/
ridirections:
https://www.gnu.org/software/bash/manual/html_node/Redirections.html

Unit tester:
https://github.com/Snaipe/Criterion
*/
#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../../libs/libft/libft.h"
# include "../parser/parser.h"
// # include "../grammer_checker/grammer_checker.h"
// # include "../executor/executor.h"

/* BNF
commandline ::= pipeline

pipeline ::=  command
          |   pipeline "|" command

command  ::=  word
          |   redirection
          |   command word
          |   command redirection

redirection  ::=  redirectionop filename
redirectionop  ::=  "<"  |  ">"  |  "<<"  |  ">>"

BNF Bash 2.0
<letter> ::= a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z| A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z 
<digit> ::= 0|1|2|3|4|5|6|7|8|9 
<number> ::= <digit> | <number> <digit> 
<word> ::= <letter> | <word> <letter> | <word> '_' 
<word_list> ::= <word> | <word_list> <word> 
<assignment_word> ::= <word> '=' <word> 
<redirection> ::= '>' <word> | '<' <word> | <number> '>' <word> | <number> '<' <word> | '>>' <word> | <number> '>>' <word> | '<<' <word> | <number> '<<' <word> | '<&' <number> | <number> '<&' <number> | '>&' <number> | <number> '>&' <number> | '<&' <word> | <number> '<&' <word> | '>&' <word> | <number> '>&' <word> | '<<-' <word> | <number> '<<-' <word> | '>&' '-' | <number> '>&' '-' | '<&' '-' | <number> '<&' '-' | '&>' <word> | <number> '<>' <word> | '<>' <word> | '>|' <word> | <number> '>|' <word> 
<simple_command_element> ::= <word> | <assignment_word> | <redirection> 
<redirection_list> ::= <redirection> | <redirection_list> <redirection> 
<simple_command> ::= <simple_command_element> | <simple_command> <simple_command_element> 
<command> ::= <simple_command> | <shell_command> | <shell_command> <redirection_list> 
<shell_command> ::= <for_command> | <case_command> | while <compound_list> do <compound_list> done | until <compound_list> do <compound_list> done | <select_command> | <if_command> | <subshell> | <group_command> | <function_def> 
<for_command> ::= for <word> <newline_list> ...
*/

/* command list
''		should prevent the shell from interpreting the meta- characters in the quoted sequence
""		hould prevent the shell from interpreting the meta- characters in the quoted sequence except for $
|		(pipe) & (fork)
<		(dup2) redirect input
>		(dup2) redirect output
<<		heredoc, repeat reading input and execute command until delimiter?
>>		(dup2) redirect output in append mode
cmd		(execve)
file	(open)
$VAR	expand VAR to the value
$?		expand to the exit status of the most recently executed foreground pipeline
*/

/* Program flow (source: http://www.aosabook.org/en/bash.html)
1	Input
1.1	Lexical
1.2	Analysis
1.3	Parsing
2	Expansion
2.1	Brace Expansion
2.2	Tilde Expansion
2.3	Varialbe and Parameter Expansion, Command, Process, Arithmetic Subitution
2.4	Word splitting
2.5	Filename generation
3	Command execution
4	Exit Status

Chapters:
3.2.2.	Variables and Parameters:
		The shell provides basic user-settable variables and some built-in variables referred to as parameters.
		
		A word beginning with a dollar sign introduces a variable or parameter reference. 
		The word, including the dollar sign, is replaced with the value of the named variable.
		
3.2.3.	The Shell Programming Language
		Reserved words introduce more complex shell commands.
		Reserved words: case, coproc, do, done, elif, else, esac, fi, for, function, if, in, select, then, until, while, {, }, [[, ]]
	
3.3.	Input Processing:
3.3.1.	Readline and command line editing:
3.3.2.	Non-interactive Input Processing:
3.3.3.	Mulitbyte Characters:
3.4.	Parsing:
		Separate the stream of characters into words and apply meaning to the result.
3.5.	Word Expansion:
3.5.1.	Parameter and Variable Expansions:
3.5.2.	And Many More:
3.5.3.	Word Splitting:
3.5.4.	Globbing:
3.5.5.	Implementation:
3.6.	Command Execution:
3.6.1.	Redirection:
3.6.2.	Builtin Commands:
3.6.2.	Simple command Execution:
3.6.4.	Job Control:
3.6.5.	Compound commands:

To do:
Make tokens, split on METACHARACTER
*/
int		shell(char *line, char **envp);
int		input_is_argv(int argc, char *argv[], char **line);
void	line_reader(char **line, const char *display_name);
void	add_line_in_history(char **line);

#endif
