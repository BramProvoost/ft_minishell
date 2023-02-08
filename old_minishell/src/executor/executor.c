/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 17:08:07 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/09 09:38:51 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

/* cmd's zijn in linked list -> execute op basis van: links, rechts, type, 
	eerste keer lezen van fd[1] - kan file zijn.
	check type - command/var/cd/pipe/&/>/>&/>>/>>&/</<</
	wachten op pid als het geen background is, anders asynchroon.
	output naar fd[1]
	lezen van fd[1]
	
	https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf

The strategy for your shell is to have the parent process do all the piping and redirection
before forking the processes. In this way the children will inherit the redirection. The parent
needs to save input/output and restore it at the end.


	Have a working history
	Search and launch the right executable (based on the PATH variable or using a
	relative or an absolute path).
	Handle ’ (single quote) which should prevent the shell from interpreting the meta-
	characters in the quoted sequence.
	Handle " (double quote) which should prevent the shell from interpreting the meta-
	characters in the quoted sequence except for $ (dollar sign).
	
	""'$variabel'"" - testen
	
	<< should be given a delimiter, then read the input until a line containing the
	delimiter is seen. However, it doesn’t have to update the history!
	>> should redirect output in append mode
	environment variables ($variabele
	$? laatste exit code

	◦ echo with option -n : -nnnnnn -n -n -n -n -nnn == valid
	◦ cd with only a relative or absolute path
	◦ pwd with no options
	◦ export with no options
	◦ unset with no options
	◦ env with no options or argument
	◦ exit with no options
	met infile en outfile?
	SHLVL
	OLDPWD
	segfault = env checken als dingen leeg zijn.
	expand
	check of env leeg is.
	
	niet: Not interpret unclosed quotes or special characters which are not required by the
	subject such as \ (backslash) or ; (semicolon).



// 4.1. read command table
// 4.x. creating pipes
// 4.x. creating processes

// execute commands op basis van wat het is. 
*/

void	execute_process(t_line_lst *stack, t_data *data, char **envp)
{
	pid_t	pid1;
	int	wstatus;

	redirect(stack, data);
	message(stack->value);
	pid1 = fork();
	if (pid1 < 0)
		message_exit("fork went wrong", 0);
	if (pid1 == 0)
	{
		message("child\n");
		dup2(data->fd[1], 1);
		close(data->fd[0]);
		dup2(1, 1);
		if (execve(data->path, data->cmd, envp) == -1)
			message_exit("execve went wrong", 0);
	}
	else
	{
		message("parent\n");
		close(data->fd[1]);
		waitpid(pid1, &wstatus, 0);
		if (WIFEXITED(wstatus))
			message("process einde\n");//, (WEXITSTATUS(wstatus)));
		// message(ft_itoa(wstatus));
		// message("\n");
	}
	return ;
	stack->type = stack->type;
}

void	execute_commands(t_line_lst *stack, t_data *data, char **envp)
{
	if (!stack || !data)
		return ;
	// if (stack->type == builtin)
	// 	execute_builtins(stack, data)
	// else if ()
	data->cmd = ft_split(stack->value, ' ');
	data->path = get_cmd_path(data->cmd[0], envp);
	if (!data->path || !data->cmd[0])
		message("geen path of splitted cmd");
	while(stack->next)
	{
		if (pipe(data->fd) < 0)
			message("pipe werkt niet");
		data->outfile = data->fd[1];
		execute_process(stack, data, envp);
		close(data->outfile);
		if (data->infile != 0)
			close(data->infile);
		data->infile = data->fd[0];
		stack = stack->next;
	}
	execute_process(stack, data, envp);
	if (data->cmd[0][0] == '\0')
		message_exit("cmd == '\0'", 1);
	if (ft_isspace(data->cmd[0][0]))
		exit(msg_custom_error_code("pipex: command not found: ", "", 0));
}

void	execute_cmd_list(t_line_lst *cmdlist, t_data *data)
{
	t_line_lst *stack;
	
	if (!cmdlist)
		return ;
	stack = cmdlist;
	// als previous is NULL en stack niet leeg -> voer commando uit met infile als die er is.
	// if (stack->prev == NULL)
	// 	execute_infile()
	// stack = stack->next
	while(stack)
	{
		//message(stack->value);
		data->fd[0] = dup(0);
		data->fd[1] = dup(1);
		execute_commands(stack, data, data->envp);
		dup2(data->fd[0], 0);
		dup2(data->fd[1], 1);
		close(data->fd[0]);
		close(data->fd[1]);
		stack = stack->next;
	}
	exit(0);
}

void	test_lists(t_line_lst *head, char **envp)
{
	t_data	data;

	data.envp = envp;
	head = NULL;
	add_at_end_of_list(&head, e_cmd, "ls");
	add_at_end_of_list(&head, e_word, "-la");
	add_at_end_of_list(&head, e_pipe, "|");
	add_at_end_of_list(&head, e_cmd, "grep");
	add_at_end_of_list(&head, e_word, "17");
	add_at_end_of_list(&head, e_pipe, "|");
	add_at_end_of_list(&head, e_cmd, "ls");
	add_at_end_of_list(&head, e_word, "-la");
	add_at_end_of_list(&head, e_pipe, "|");
	add_at_end_of_list(&head, e_cmd, "grep");
	add_at_end_of_list(&head, e_word, "17");
	// add_at_end_of_list(&head, e_cmd, "grep gitignore");
	//add_at_end_of_list(&head, e_file, "outfile.txt");
	show_t_list(head, "Put here the input line as reference");
	printf("length of list is %d\n", length_of_list(head));
	execute_cmd_list(head, &data);
	//delete_list(&head);
	//show_list(head);
	//printf("length of list is %d\n", length_of_list(head));
}
