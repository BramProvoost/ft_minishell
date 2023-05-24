/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   struct_printer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 18:08:04 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/05/24 19:14:00 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	temp_t_cmd_printer(t_cmd *cmd, char *header)
{
	int		i;
	int		j;
	t_file	*tmp_file;

	i = 0;
	printf(BLUE"%s"NC"\n", header);
	while (cmd)
	{
		if (cmd->exec)
		{
			if (cmd->exec->cmd_path)
				printf(GRAY"cmd[%d]->exec->cmd_path = '"GREEN"%s"GRAY"'"NC"\n",
					i, cmd->exec->cmd_path);
			if (cmd->exec->cmd_args)
			{
				j = 0;
				while (cmd->exec->cmd_args[j])
				{
					printf(GRAY"cmd[%d]->exec->cmd_args[%d] = '"GREEN"%s\
						"GRAY"' "NC"\n", \
						i, j, cmd->exec->cmd_args[j]);
					j++;
				}
			}
		}
		tmp_file = cmd->file;
		j = 0;
		while (tmp_file)
		{
			printf(GRAY"cmd[%d]->file[%d]->type = '"GREEN"%s"GRAY"'"NC"\n",
				i, j, temp_type_to_string(tmp_file->type));
			printf(GRAY"cmd[%d]->file[%d]->file_name = '"GREEN"%s"GRAY"'"NC"\n",
				i, j, tmp_file->file_name);
			printf(GRAY"cmd[%d]->file[%d]->delimiter = '"GREEN"%s"GRAY"'"NC"\n",
				i, j, tmp_file->delimiter);
			tmp_file = tmp_file->next;
			j++;
		}
		cmd = cmd->next;
		i++;
	}
	printf(BLUE"End %s"NC"\n", header);
}
