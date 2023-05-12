/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_token.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edawood <edawood@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 16:47:48 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/12 12:27:06 by bprovoos      ########   odam.nl         */
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
		free_2d(temp->paths);
		free(temp);
	}
}

t_token *create_token(void)
{
	t_token *new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		ft_putendl_fd("malloc fail", 1);
		exit(1);
	}
	return (new_token);
}

t_token	*last_token(t_token *lst)
{
	if (!lst)
		return (create_token());
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	add_token_back(t_token **lst, t_token *new_token)
{
	t_token	*last;

	if (!*lst)
		*lst = new_token;
	else
	{
		last = last_token(*lst);
		last->next = new_token;
		new_token->prev = last;
	}
}
