/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pwd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edawood <edawood@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:08:41 by edawood           #+#    #+#             */
/*   Updated: 2023/05/22 18:39:55 by edawood          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	minishell_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("pwd: error retrieving current directory: getcwd: "
			"cannot access parent directories: No such file or directory", 1);
		return (SUCCESS);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (SUCCESS);
}
