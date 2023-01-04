/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:31:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/04 16:01:00 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define METACHARACTER " \t\n|&;()<>"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../old_minishell/libs/libft/libft.h"
// # include <readline.h>

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
	void			*value;
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
void	delete_tokens(t_token *lst);

void	print_tokens(t_token *token);

#endif
