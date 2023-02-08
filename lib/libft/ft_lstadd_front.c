/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_front.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 21:54:40 by bprovoos      #+#    #+#                 */
/*   Updated: 2020/12/17 17:46:47 by bramjr        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** --------------new-------------              --------------lst-------------
** |              |             |            \ |              |             |
** |   CONTENT    |     NEXT    |--------------|   CONTENT    |     NEXT    |
** |              |             |            / |              |             |
** ------------------------------              ------------------------------
** https://www.learn-c.org/en/Linked_lists
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
