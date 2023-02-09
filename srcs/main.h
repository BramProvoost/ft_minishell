/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:31:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/09 11:13:48 by bprovoos      ########   odam.nl         */
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
# include "../lib/libft/libft.h"

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
void	temp_print_tokens(t_token *token);

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
