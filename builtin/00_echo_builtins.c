/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_echo_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:03:10 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 17:16:14 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	echo_builtins(t_cmd *cmd, int i)
{
	int		i;
	bool	flag;

	i = 1;
	if (ft_strncmp(cmd[i].cmd[i], "-n", 3) == 0)
	{
		flag = true;
		i++;
	}
	while (cmd[i].cmd[i])
	{
		ft_putstr(cmd[i].cmd[i]);
		if (cmd[i].cmd[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!flag)
		ft_putchar('\n');
	return (0);
}
