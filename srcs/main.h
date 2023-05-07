/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:31:40 by bprovoos          #+#    #+#             */
/*   Updated: 2023/05/07 20:15:47 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# define METACHARACTER " \t\n|&;()<>"
# define NC "\033[0m"
# define RED "\033[38;5;1m"
# define GREEN "\033[38;5;2m"
# define YELLOW "\033[38;5;3m"
# define BLUE "\033[38;5;4m"
# define MAGENTA "\033[38;5;5m"
# define CYAN "\033[38;5;6m"
# define WHITE "\033[38;5;7m"
# define GRAY "\033[38;5;8m"

# define CHILD 0
# define READ 0
# define WRITE 1
# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define ERROR -1
# define SUCCESS 0
# define OUTPUT 1
# define APPEND 2


# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"


/* Global variable declaration */
int	g_exit_status;

typedef enum e_type {
	WORD,
	CMD,
	PIPE,
	FILE_T,
	INPUT_SINGLE,
	HEREDOC,
	OUTPUT_SINGLE,
	OUTPUT_APPEND,
}	t_type;

typedef struct s_token {
	t_type			type;
	char			**paths;
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


/// @param cmd_path path and command
/// @param cmd_args command and arguments
typedef struct s_exec
{
	char	*cmd_path;
	char	**cmd_args;
	int		len;
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
	bool			echo_n_flag;
	bool			echo_print_flag;
	bool			echo_arg;
	// char			*arg;
	t_exec			*exec;
	struct s_file	*file;
	struct s_cmd	*next;
}	t_cmd;

typedef struct exec_data
{
	t_cmd		*cmd;
	t_env		*env;
	t_token		*tokens;
	bool		is_pipe;
	int			pipe_fds[2];
}	t_exec_data;

// verwijder next en heredoc. Gebruik andere enum
typedef struct s_file {
	t_type			type;
	char			*file_name;
	char			*delimiter;
	struct s_file	*next;
}	t_file;

typedef struct s_heredoc
{
	char				*delimiter;
	struct s_heredoc	*next;
}	t_heredoc;

/* main.c */
char	**get_paths(t_env *env);

/* line_reader.c */
void	line_reader(char **line, const char *display_name);

/* tokenizer.c */
t_token	*tokenizer(char *raw_line);
void	delete_tokens(t_token *lst);
void	data_to_token(t_token **token, t_line *line);
void	temp_print_tokens(t_token *tokens, char *header);
void	quote_case(t_line *line);

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

/* cmds_handler.c */
char	*get_full_cmd(char *cmd, char **paths);

/* add_cmd.c */
t_cmd	*new_t_cmd(void);
void	add_t_cmd_back(t_cmd *cmd);
void	path_and_cmd_to_t_cmd(t_cmd **cmd, char **split_cmd_and_args, t_env *env);
void	file_to_t_cmd(t_cmd **cmd, t_type type, char *value);
void	free_t_cmd(t_cmd *cmd);
void	temp_t_cmd_printer(t_cmd *cmd, char *header);

/* temp_token_printer.c */
char	*temp_type_to_string(t_type type);

/* expander.c */
void	temp_print_tokens(t_token *tokens, char *header);
void	expander(t_token **tokens, t_env *env);

//Executor functions
void	executor(t_cmd *cmd, t_token *tokens, t_env *env);
void	ft_execute(t_exec_data *exec_data);
void	child_process(t_exec_data *exec_data, int prev_fd);
void	close_fds(int *pipe_fds, int fd_in, bool is_pipe);
void	wait_for_pids(pid_t pid);
void	exec_data_init(t_exec_data *exec_data, t_cmd *cmd, t_token *tokens, t_env *env);
void	set_cmd_to_next(t_exec_data *exec_data);
void	close_pipes(int pipe_fds[2]);
bool	has_pipe(t_cmd *cmd);

//Path generator functions
char	*get_all_paths(char *path, t_env *env);
void	free_2d(char **paths);
char	**ft_strdup2d(char **str);

//Errors functions
void	error_cmd_not_found(char *cmd);
int		file_error(char *filename);
void	error_exit(int code, char *cmd);
void	ft_error(void);
int		chdir_error(char *str, int32_t error);

//File handler functions
int		duplicate(int fd, int fileno);
int		redirect_input(t_exec_data *exec_data, int fd);
int		redirect_output(t_exec_data *exec_data);
void    redirect_in_simple_cmd(t_exec_data *exec_data);
int		heredoc(t_exec_data *exec_data);
int		run_heredoc(t_file *file);
int		create_heredoc_file(char *delimiter, char *file_name);

//built-in functions
int		is_buld_in_cmd(char *cmd);
int		execute_built_in_cmd(t_exec_data *exec_data, char *cmd);
int		minishell_cd(t_cmd *cmd, t_env *env);
int		minishell_echo(t_cmd *cmd);
int		minishell_pwd();
int		minishell_export(t_cmd *cmd, t_env *env);
void	print_export(t_env *env);
void	export_util(char *key, char *value, t_env *env);
bool    export_error(char *str);
bool	is_not_alpha(char *str);
bool	is_not_alpha_second_arg(char *str);
bool	check_if_cmd_is_word(t_cmd *cmd, int i);
void	set_env(char *key, char *value, t_env *env);
int		minishell_exit(char *arg, t_exec_data *exec_data);
int		minishell_unset(t_cmd *cmd, t_env *env);

//env functions
int		minishell_env(t_env *env);
void	free_env_list(t_env **head);
t_env	*new_env_node(char *env);
bool	create_env_list(t_env **head, char **envp);
char	**env_to_list(t_env *env);
int		get_env_len(t_env *env);
void    assign_env_value(t_env *new, char *env, int i, int len);

#endif
