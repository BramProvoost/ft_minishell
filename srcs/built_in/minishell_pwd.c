/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell_pwd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/22 16:08:41 by edawood       #+#    #+#                 */
/*   Updated: 2023/02/09 11:27:45 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ERROR);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (SUCCESS);
}
