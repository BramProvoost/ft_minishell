/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:34:00 by edawood           #+#    #+#             */
/*   Updated: 2023/05/03 21:05:27 by edawood          ###   ########.fr       */
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

void	error_exit(int code, char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putendl_fd(": no such file or directory", 2);
	exit(code);
}

int	file_error(char *filename)
{
	if (!filename)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putendl_fd("ambiguous redirect", STDERR_FILENO);
		ft_putendl_fd("No such file or directory", STDERR_FILENO);
		return (1);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (filename)
	{
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd("Permission denied", STDERR_FILENO);
		g_exit_status = 126;
	}
	return (1);
}

void	error_cmd_not_found(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": no such file or directory", 2);
		exit(127);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
}
