/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 14:56:55 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

/*
The function ft_echo is used to print the arguments.
*/

int	ft_echo(t_cmd *cmd, int index)
{
	int		args;
	bool	flag;

	args = 1;
	if (ft_strncmp(cmd[index].cmd[args], "-n", 3) == 0)
	{
		flag = true;
		args++;
	}
	while (cmd[index].cmd[args])
	{
		ft_putstr(cmd[index].cmd[args]);
		if (cmd[index].cmd[args + 1])
			ft_putchar(' ');
		args++;
	}
	if (!flag)
		ft_putchar('\n');
	return (CMD_OK);
}
