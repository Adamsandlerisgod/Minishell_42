/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:16:21 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 00:05:21 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

/*
The function is_builtins is used to check if the command is a builtin.
*/

bool	is_builtins(t_data *data, int index)
{
	if (ft_strncmp(data->cmd[index], "echo", 6) == 0 || \
		ft_strncmp(data->cmd[index], "cd", 3) == 0 || \
		ft_strncmp(data->cmd[index], "pwd", 4) == 0 || \
		ft_strncmp(data->cmd[index], "export", 7) == 0 || \
		ft_strncmp(data->cmd[index], "unset", 6) == 0 || \
		ft_strncmp(data->cmd[index], "env", 4) == 0 || \
		ft_strncmp(data->cmd[index], "exit", 5) == 0)
		return (true);
	return (false);
}

/*
The function execute_builtins is used to execute the builtin commands.
*/

int	execute_builtins(t_data *data, char **env, int index)
{
	if (ft_strncmp(data->cmd[index], "echo", 6) == 0)
		return (ft_echo(data, index));
	else if (ft_strncmp(data->cmd[index], "cd", 3) == 0)
		return (ft_cd(data, index));
	else if (ft_strncmp(data->cmd[index], "pwd", 4) == 0)
		return (ft_pwd(data, index));
	else if (ft_strncmp(data->cmd[index], "export", 7) == 0)
		return (ft_export(data, env, index));
	else if (ft_strncmp(data->cmd[index], "unset", 6) == 0)
		return (ft_unset(data, index));
	else if (ft_strncmp(data->cmd[index], "env", 4) == 0)
		return (ft_env(data, env, index));
	else if (ft_strncmp(data->cmd[index], "exit", 5) == 0)
		return (ft_exit(data, index));
	return (CMD_NOT_FOUND);
}
