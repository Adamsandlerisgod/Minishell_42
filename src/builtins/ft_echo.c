/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:46 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 00:35:26 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_echo is used to print the arguments with newline.
With the option "-n" it print it withou newline.
*/

static bool	is_option_echo(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == 45)
	{
		if (ft_strlen(&arg[i]) == 1)
			return (false);
		i++;
		while (arg[i])
		{
			if (arg[i] != 110)
				return (false);
			i++;
		}
		return (true);
	}
	return (false);
}

static void	print_echo(char **args, bool flag, int i)
{
	if (!args[i])
	{
		if (!flag)
			printf("\n");
		return ;
	}
	while (args[i])
	{
		if (is_option_echo(args[i]) == true && i == 1)
			i++;
		else
		{
			printf("%s", args[i]);
			if (args[i + 1])
				printf(" ");
			else if (!args[i + 1] && !flag)
				printf("\n");
			i++;
		}
	}
}

void	ft_echo(t_data *data, int index)
{
	bool	flag;

	flag = false;
	if (data->cmd[index].cmd[1])
	{
		if (is_option_echo(data->cmd[index].cmd[1]) == true)
			flag = true;
	}
	print_echo(data->cmd[index].cmd, flag, 1);
	g_exit_status = CMD_OK;
}
