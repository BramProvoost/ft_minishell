/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/15 15:00:48 by bprovoos      #+#    #+#                 */
/*   Updated: 2021/05/27 17:54:18 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ------------------------------              -------------node-------------
** |              |             |            \ |              |             |
** |   CONTENT    |     NEXT    |--------------|   CONTENT    |     NEXT    |
** |              |             |            / |              |             |
** ------------------------------              ------------------------------
** https://www.learn-c.org/en/Linked_lists
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}
