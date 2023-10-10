/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:21:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/11 00:26:54 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/execute.h"

void	free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_cmd_struct(t_cmd *cmd)
{
	int i;

	i = 0;
	free_2d_array(cmd->cmd);
	free_2d_array(cmd->limiters);
	free_2d_array(cmd->infiles);
	free_2d_array(cmd->outfiles);
	while (cmd)
		free(cmd);
	free(cmd);
}
