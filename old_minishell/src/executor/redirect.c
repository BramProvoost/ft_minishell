/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirect.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dyeboa <dyeboa@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 11:36:37 by dyeboa        #+#    #+#                 */
/*   Updated: 2022/11/03 13:58:05 by dyeboa        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void    redirect(t_line_lst *stack, t_data *data)
{
    t_line_lst *temp;

    temp = stack;
    while(temp && temp->type != e_pipe )
    {
        if (temp->type == e_redirect_i)
            open_infile(temp->value, data);
        // if (temp->type == e_delimiter)
        //     open_till(temp->value, data, temp->next->value);
        if (temp->type == e_redirect_o || temp->type == e_append)
             open_outfile(temp->value , data, temp->type);
		temp = temp->next;
    }
	return ;
}