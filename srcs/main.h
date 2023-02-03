/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:31:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/01 17:46:26 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define METACHARACTER " \t\n|&;()<>"
# define NC "\033[0m"
# define GREEN "\033[38;5;2m"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../old_minishell/libs/libft/libft.h"

/* Global variable declaration */
int	g_last_pid;

typedef enum e_type {
	WORD,
	CMD,
	PIPE,
	INPUT_S,
	INPUT_D,
	OUTPUT_S,
	OUTPUT_D
}	t_type;

typedef struct s_token {
	t_type			type;
	char			*value;
	long			len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_line {
	char	quote;
	long	position;
	long	len;
	char	*text;
}	t_line;

/* line_reader.c */
void	line_reader(char **line, const char *display_name);

/* tokenizer.c */
t_token	*tokenizer(char *raw_line);
void	delete_tokens(t_token *lst);
void	data_to_token(t_token **token, t_line *line);
void	print_tokens(t_token *token);

/* hande_token.c */
void	delete_tokens(t_token *head);
t_token *create_token(void);
t_token	*last_token(t_token *lst);
void	add_token_back(t_token **lst, t_token *new);

/* line_functions.c */
void	next_char(t_line *line);
char	get_next_char(t_line line);
char	get_current_char(t_line line);
char	get_prev_char(t_line line);
void	move_position(t_token *token_lst, t_line *line);

/* case_handler.c */
void	pipe_case(t_token **token);
void	input_case(t_token **token, t_line line);
void	output_case(t_token **token, t_line line);
void	word_case(t_token **token, t_line *line);

/* check_grammer.c */
int	gramer_is_valid(t_token *tokens);

/* signals.c */
void	init_signals(void);

#endif

/* 
What is the program flow for a lexer, tokenizer and parser?

The program flow for a lexer, tokenizer, and parser typically works as follows:
1. The lexer takes in a stream of characters as input and produces a stream of tokens (lexemes) as output.
2. The tokenizer takes in the stream of tokens from the lexer and groups them into higher-level constructs called phrases.
3. The parser takes in the stream of phrases from the tokenizer and generates a parse tree or an abstract syntax tree (AST) 
that represents the structure of the input according to the rules of the language being parsed.

Here is a more detailed description of each step:

1. Lexing:
- The lexer scans the input characters one by one, identifying the lexemes (tokens) in the input.
- A lexeme is a sequence of characters that belongs to the same token class (e.g., identifier, keyword, operator, etc.).
- The lexer uses regular expressions or a set of rules to identify the lexemes in the input.
- For each lexeme, the lexer creates a token that consists of a token type and a lexeme value, and adds it to the output stream of tokens.

2. Tokenizing:
- The tokenizer takes in the stream of tokens from the lexer and groups them into phrases.
- A phrase is a group of tokens that form a higher-level construct in the language, such as a statement or an expression.
- The tokenizer uses the syntax rules of the language to identify the phrases in the input.
- For each phrase, the tokenizer creates a phrase object and adds it to the output stream of phrases.

3. Parsing:
- The parser takes in the stream of phrases from the tokenizer and generates a parse tree or an AST that represents the structure of the input.
- A parse tree is a tree-like representation of the syntactic structure of the input, with the root of the tree being the overall structure of 
the input and the leaves being the individual tokens.
- An AST is a simplified version of the parse tree that only includes the information needed for further processing, such as type checking and 
code generation.
- The parser uses the syntax rules of the language to build the parse tree or AST.
- The parse tree or AST can then be used for various purposes, such as interpreting or compiling the input.
*/

/*
A tokenizer breaks a stream of text into tokens, usually by looking for whitespace (tabs, spaces, new lines).

A lexer is basically a tokenizer, but it usually attaches extra context to the tokens -- this token is a number, that token is a 
string literal, this other token is an equality operator.

A parser takes the stream of tokens from the lexer and turns it into an abstract syntax tree representing the (usually) program 
represented by the original text.
 */
