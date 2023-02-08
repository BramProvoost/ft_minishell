#ifndef executor_H
# define executor_H
# include "./lib/libft/libft.h"
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdio.h>

#define CHILD 0
#define READ 0
#define WRITE 1
#define STDIN 0
#define STDOUT 1
#define STDERR 2
#define ERROR -1
#define SUCCESS 0

typedef struct s_exec
{
    char    *exec;
    char    **args;
    int     len;
}   t_exec;

typedef struct s_env
{
    char    *key;
    char    *value;
    bool    has_value;
    struct s_env    *next;
}   t_env;

typedef struct s_child_pids
{
	pid_t				pid;
	struct s_child_pids	*next;
}	t_child_pids;

typedef struct s_cmd
{
    t_exec          *exec;
    char            *arg;
    struct s_cmd    *next;
    struct s_file   *file;
}	t_cmd;

typedef struct s_args
{
    char    **paths;
    t_env   *env;
    int     env_len;
    int     status_code;
    bool    has_pipes;
    char    *home_path;
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

//Executor functions
void    executor(t_cmd *cmd, t_args *args);
void    ft_execute(t_cmd *cmd, t_args *args);
void	child_process(t_cmd *cmd, t_args *args, int fd[2], int prev_fd);
void	close_fds_run_with_pipes(int *pipe_fds, int fd_in);
void	wait_for_pids(t_args *args);

//Path generator functions
char    **init_paths(t_args *args);
char    *get_all_paths(char *path, t_env *env);
void	free_2d(char **paths);

//Errors functions
void	error_cmd_not_found(char *cmd);
int     file_error(char *filename);
void	error_exit(int code, char *cmd);
void	ft_error(void);
int	    chdir_error(char *str, int32_t error);

//File handler functions
int     duplicate(t_args *args, int fd, int fileno);
int     redirect_input(t_cmd *cmd, t_args *args, int fd);
int     redirect_output(t_cmd *cmd, t_args *args, int fd);
int     heredoc(t_cmd *cmd, t_args *args);
int     run_heredoc(t_cmd *cmd, t_args *args, char *delimiter);
int     create_heredoc_file(char *delimiter, char *file_name);

//built-in functions
int     is_built_in_cmd(t_cmd *cmd_list, char *cmd, t_args *args);
int     minishell_cd(char *arg, t_cmd *cmd, t_args *args);
int     minishell_echo(char *arg, t_cmd *cmd);
int     minishell_pwd();
int     minishell_export(char *arg, t_cmd *cmd, t_args *args);
int     minishell_exit(char *arg, t_cmd *cmd, t_args *args);
int     minishell_unset(t_cmd *cmd, t_args *args);

//env functions
int     minishell_env(t_env *env);
void    free_env_list(t_env **head);
t_env   *new_env_node(char *env);
bool    create_env_list(t_env **head, char **envp);

#endif