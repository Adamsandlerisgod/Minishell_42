/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:55 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/11 20:25:54 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	ft_isnumber(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	get_exit_status(t_data *data, char *arg)
{
	int	status;

	(void) data;
	status = 0;
	if (arg)
	{
		if (ft_isnumber(arg))
			status = (ft_atol(arg)%256);
		else
		{
			error_cmd("exit", "numeric argument required");
			status = 255;
		}
	}
	else
		status = CMD_OK;
	return (status);
}

/*
The function ft_exit is used to exit the minishell.
It returns the exit status.
*/

int	ft_exit(t_data *data, int index)
{
	int	status;

	status = get_exit_status(data, data->cmd[0].cmd[1]);
	if (data->cmd[index].pipe_out == true
		|| data->cmd[index].pipe_in == true)
		return (status);
	ft_putendl_fd("exit", STDOUT_FILENO);
	// call exit function of minishell
	exit (status);
}
