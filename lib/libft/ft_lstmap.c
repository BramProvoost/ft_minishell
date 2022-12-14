/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bramjr <bramjr@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/17 17:49:32 by bramjr        #+#    #+#                 */
/*   Updated: 2021/05/27 17:54:28 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** +--------------+-------------+              +--------------+-------------+
** |              |             |            \ |              |             |
** |   CONTENT    |     NEXT    |--------------|   CONTENT    |     NEXT    |
** |              |             |            / |              |             |
** +--------------+-------------+              +--------------+-------------+
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*current_link;

	new_list = NULL;
	while (lst)
	{
		current_link = ft_lstnew((*f)(lst->content));
		if (current_link == NULL)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, current_link);
		lst = lst->next;
	}
	return (new_list);
}
