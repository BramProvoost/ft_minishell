/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:42:28 by edawood           #+#    #+#             */
/*   Updated: 2023/05/26 21:27:15 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	ft_error(void)
{
	perror("Minishell");
	exit(errno);
}

bool	export_error(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (false);
}

void	error_heredoc(char *file_name, t_exec_data *exec_data)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putendl_fd(": No such file or directory", 2);
	unlink_heredoc_files(exec_data);
	exit(1);
}

void	error_exit(int code, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": no such file or directory", 2);
	exit(code);
}

int	error_ambiguous(void)
{
	ft_putendl_fd("minishell: ambiguous redirect", 2);
	g_exit_status = 1;
	return (ERROR);
}

// char	*error_path(void)
// {
// 	ft_putstr_fd("minishell: ", 2);
// 	ft_putstr_fd(cmd, 2);
// 	ft_putendl_fd(": no such file or directory", 2);
// }
