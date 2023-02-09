/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 16:47:48 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/01/27 11:05:09 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	delete_tokens(t_token *head)
{
	t_token	*temp;

	while (head && head->next != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

t_token *create_token(void)
{
	t_token *new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (new);
}

t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (create_token());
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_token_back(t_token **lst, t_token *new)
{
	t_token	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = last_token(*lst);
		last->next = new;
		new->prev = last;
	}
}
