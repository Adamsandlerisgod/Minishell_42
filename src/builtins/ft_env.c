/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:51 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/10 23:26:10 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function env_builtins is used to print the environment variables.
Check if the command has an option or an argument.
*/

int	ft_env(t_data *data, char **env, int index)
{
	if (data->cmd[index].cmd[1])
	{
		error_cmd(data->cmd[index].cmd[0], "no option or argument accepted.");
		return (CMD_EXIT);
	}
	print_env(env);
	return (CMD_OK);
}
