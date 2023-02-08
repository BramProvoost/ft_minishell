/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 19:12:35 by bprovoos      #+#    #+#                 */
/*   Updated: 2020/12/16 20:59:56 by bramjr        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** --------------lst-------------              --------------new-------------
** |              |             |            \ |              |             |
** |   CONTENT    |     NEXT    |--------------|   CONTENT    |     NEXT    |
** |              |             |            / |              |             |
** ------------------------------              ------------------------------
** https://www.learn-c.org/en/Linked_lists
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ft_lstlast(*lst)->next = new;
}
