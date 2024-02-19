/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:51 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 01:02:12 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_env is used to print the environment variables.
Check if the command has an option or an argument.
*/

void	ft_env(t_data *data, char **env, int index)
{
	if (data->cmd[index].cmd[1])
	{
		error_cmd_msg("env", data->cmd[index].cmd[1], NO_OPT_ARG);
		g_exit_status = CMD_ERROR;
	}
	else
		print_env(env, 0);
}
