#ifndef executor_H
# define executor_H
# include "./lib/libft/libft.h"
# include <errno.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct cmd
{
    char            **cmd;
    struct s_cmd    *next;
}	t_cmd;

typedef struct args
{
    char    *paths;
    char    **env;
}	t_args;

void    executor(t_cmd *cmd, t_args *args);
char    *init_paths(char **cmd, char **env);

#endif