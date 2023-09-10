/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_exit_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:03:19 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 20:06:17 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static int	get_exit_status(char *arg)
{

}

int	exit_builtins(t_data *data, char **ev, int i)
{
	int	status;

	status = 0;

	if (data->cmd[i - 1].pipe == true || data->cmd[i].pipe == true)
		return (1);
	else
	{
		free_struct(data);
		free_tab(ev);
	}
	ft_putendl_fd("exit", 1);
	exit (status);
}
