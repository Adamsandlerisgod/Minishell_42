/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:55 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 19:59:32 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_exit is used to exit the minishell.
It returns the exit status.
*/

static int	quit_and_clean(t_data *data)
{
	rl_clear_history();
	free_env(data->env);
	free_data_struct(data);
	exit (g_exit_status);
}

static bool	ft_isnumber(char *arg, bool flag)
{
	int	i;

	i = 0;
	if (flag == true)
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
	}
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	check_input_exit(t_data *data, int index)
{
	if (data->cmd[index].cmd[1] != NULL)
	{
		if (data->cmd[index].cmd[2] != NULL
			&& ft_isnumber(data->cmd[index].cmd[1], false)
			&& check_long_long(data->cmd[index].cmd[1]) == true)
		{
			error_exit_msg(NULL, TOO_MANY_ARG, 1);
			g_exit_status = CMD_ERROR;
			return (1);
		}
	}
	return (0);
}

static void	get_exit_status(t_data *data, char *arg, int flag)
{
	if (arg != NULL)
	{
		if (check_long_long(arg) == false || !ft_isnumber(arg, true))
		{
			error_exit_msg(arg, NUM_ARG, flag);
			g_exit_status = 255;
			quit_and_clean(data);
		}
		else
			g_exit_status = (ft_atoll(arg) % 256);
	}
	else
		g_exit_status = CMD_OK;
}

void	ft_exit(t_data *data, int index)
{
	int	flag;

	flag = 0;
	if (data->pipe_len > 1)
		flag = 1;
	flag = check_input_exit(data, index);
	if (g_exit_status == CMD_OK)
		get_exit_status(data, data->cmd[0].cmd[1], flag);
	error_exit_msg(NULL, NULL, flag);
	if (flag == 0)
		quit_and_clean(data);
}
