/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/07 19:31:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/02/09 11:26:14 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define METACHARACTER " \t\n|&;()<>"
# define NC "\033[0m"
# define GREEN "\033[38;5;2m"

#define CHILD 0
#define READ 0
#define WRITE 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define ERROR -1
#define SUCCESS 0

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
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

typedef struct s_exec
{
	char	*exec;
	char	**args;
	int	len;
}	t_exec;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	has_value;
	struct s_env	*next;
}	t_env;

typedef struct s_child_pids
{
	pid_t				pid;
	struct s_child_pids	*next;
}	t_child_pids;

typedef struct s_cmd
{
	t_exec			*exec;
	char			*arg;
	struct s_cmd	*next;
	struct s_file	*file;
}	t_cmd;

typedef struct s_args
{
	char	**paths;
	t_env	*env;
	int		env_len;
	int		status_code;
	bool	has_pipes;
	char	*home_path;
}	t_args;

typedef enum s_file_type {
	INPUT_SINGLE,
	INPUT_DOUBLE,
	HEREDOC,
	OUTPUT_SINGLE,
	OUTPUT_APPEND,
}	t_file_type;

typedef struct s_file {
	t_file_type		type;
	char			*file_name;
	int				heredoc;
	struct s_file	*next;
}	t_file;

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
int		gramer_is_valid(t_token *tokens);

/* signals.c */
void	init_signals(void);

//Executor functions
void	executor(t_cmd *cmd, t_args *args);
void	ft_execute(t_cmd *cmd, t_args *args);
void	child_process(t_cmd *cmd, t_args *args, int fd[2], int prev_fd);
void	close_fds_run_with_pipes(int *pipe_fds, int fd_in);
void	wait_for_pids(t_args *args);

//Path generator functions
char	**init_paths(t_args *args);
char	*get_all_paths(char *path, t_env *env);
void	free_2d(char **paths);

//Errors functions
void	error_cmd_not_found(char *cmd);
int		file_error(char *filename);
void	error_exit(int code, char *cmd);
void	ft_error(void);
int		chdir_error(char *str, int32_t error);

//File handler functions
int		duplicate(t_args *args, int fd, int fileno);
int		redirect_input(t_cmd *cmd, t_args *args, int fd);
int		redirect_output(t_cmd *cmd, t_args *args, int fd);
int		heredoc(t_cmd *cmd, t_args *args);
int		run_heredoc(t_cmd *cmd, t_args *args, char *delimiter);
int		create_heredoc_file(char *delimiter, char *file_name);

//built-in functions
int		is_built_in_cmd(t_cmd *cmd_list, char *cmd, t_args *args);
int		minishell_cd(char *arg, t_cmd *cmd, t_args *args);
int		minishell_echo(char *arg, t_cmd *cmd);
int		minishell_pwd();
int		minishell_export(char *arg, t_cmd *cmd, t_args *args);
int		minishell_exit(char *arg, t_cmd *cmd, t_args *args);
int		minishell_unset(t_cmd *cmd, t_args *args);

//env functions
int		minishell_env(t_env *env);
void	free_env_list(t_env **head);
t_env	*new_env_node(char *env);
bool	create_env_list(t_env **head, char **envp);

#endif
