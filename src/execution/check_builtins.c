/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:16:21 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/22 20:40:28 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

bool	check_builtins(t_data *data, int index)
{
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(data->cmd, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(data->cmd, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(data->cmd, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(data->cmd, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(data->cmd, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(data->cmd, "exit", 4) == 0)
		return (true);
	return (false);
}

int	execute_buitlins(t_data *data, int index)
{
	if (ft_strncmp(data->cmd, "echo", 5) == 0)
		return (ft_echo(data->cmd, index));
	else if (ft_strncmp(data->cmd, "cd", 2) == 0)
		return (ft_cd(data->cmd, data->env, index));
	else if (ft_strncmp(data->cmd, "pwd", 3) == 0)
		return (ft_pwd(data->cmd, index));
	else if (ft_strncmp(data->cmd, "export", 6) == 0)
		return (ft_export(data->cmd, data->env, index));
	else if (ft_strncmp(data->cmd, "unset", 5) == 0)
		return (ft_unset(data->cmd, data->env, index));
	else if (ft_strncmp(data->cmd, "env", 3) == 0)
		return (ft_env(data->env, index));
	else if (ft_strncmp(data->cmd, "exit", 4) == 0)
		return (ft_exit(data->cmd, index));
	return (CMD_NOT_FOUND);
}
