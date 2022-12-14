/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:31:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/14 09:25:32 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// # define METACHARACTER " \t\n|&;()<>"

# include <stdlib.h>
# include <stdio.h>
// # include <readline.h>

typedef enum e_type {
	WORD,
	PIPE,
	INPUT_S,
	INPUT_D,
	OUTPUT_S,
	OUTPUT_D,
	TOKEN_EOF,
}	t_type;

typedef struct s_token {
	t_type			type;
	char			*text;
	long			len;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_line {
	char	*text;
	long	len;
	long	position;
}	t_line;

/* tokenizer.c */
t_token	*tokenizer(char *raw_line);

#endif
