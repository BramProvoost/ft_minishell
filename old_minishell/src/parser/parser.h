/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:46:28 by bprovoos      #+#    #+#                 */
/*   Updated: 2022/12/02 11:02:44 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define METACHARACTER " \t\n|&;()<>"

# include "../../libs/libft/libft.h"
# include "../expander/expander.h"
# include <stdlib.h>

/* 
The basic data structure the shell uses to pass information from one stage to the next, 
and to operate on data units within each processing stage.
*/
typedef struct	s_word_desc {
	char	*word;
	int		flags;
}	t_word_desc;

/*
A simple command is a word_list, the result of expansion is a word_list, 
and the built-in commands each take a word_list of arguments.
*/
typedef struct	s_word_list {
	t_word_desc			*word;
	struct	s_word_list	*next;
}	t_world_list;

/*
Struct for the command line.
*/
typedef struct s_cmd_line {
	char				*cmd;
	char				**args;
	struct s_cmd_line	*next;
}	t_cmd_line;

t_world_list	*parser(char *line);

#endif
