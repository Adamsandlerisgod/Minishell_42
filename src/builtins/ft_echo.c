/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/16 16:30:20 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_echo is used to print the arguments.
*/

int	ft_echo(t_data *data, int index)
{
	int		args;
	bool	flag;

	args = 1;
	if (ft_strncmp(data->cmd[index].cmd[args], "-n", 3) == 0)
	{
		flag = true;
		args++;
	}
	while (data->cmd[index].cmd[args])
	{
		ft_putstr(data->cmd[index].cmd[args]);
		if (data->cmd[index].cmd[args + 1])
			ft_putchar(' ');
		args++;
	}
	if (!flag)
		ft_putchar('\n');
	return (CMD_OK);
}
