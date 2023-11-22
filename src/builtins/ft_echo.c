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

static bool	have_new_line(char *arg)
{
	int	i;
	bool	flag;

	flag = false;
	i = 0;
	if (arg[i] != '-')
		return (flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		flag = true;
	return (flag);
}

static void	print_echo(char **args, bool flag, int i)
{
	if (!args[i])
	{
		if (!flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		else if (!args[i + 1] && !flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	ft_echo(t_data *data, int index)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	while (data->cmd[index].cmd[i] && have_new_line(data->cmd[index].cmd[i]))
	{
		flag = true;
		i++;
	}
	print_echo(data->cmd[index].cmd, flag, i);
	return (CMD_OK);
}
