/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 16:16:21 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 15:38:30 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The file contain the function related to the execution of the builtins
commands.
*/

static bool	is_parent_builtin(t_data *data, int index)
{
	if (ft_strncmp(data->cmd[index].cmd[0], "exit", 5) == 0
		|| (ft_strncmp(data->cmd[index].cmd[0], "export", 7) == 0
			&& data->cmd[index].cmd[1] != NULL)
		|| ft_strncmp(data->cmd[index].cmd[0], "unset", 6) == 0
		|| ft_strncmp(data->cmd[index].cmd[0], "cd", 3) == 0)
		return (true);
	return (false);
}

bool	is_builtins(t_data *data, int index)
{
	if (data->cmd[index].cmd[0] != NULL)
	{
		if (ft_strncmp(data->cmd[index].cmd[0], "echo", 5) == 0
			|| ft_strncmp(data->cmd[index].cmd[0], "cd", 3) == 0
			|| ft_strncmp(data->cmd[index].cmd[0], "pwd", 4) == 0
			|| ft_strncmp(data->cmd[index].cmd[0], "export", 7) == 0
			|| ft_strncmp(data->cmd[index].cmd[0], "unset", 6) == 0
			|| ft_strncmp(data->cmd[index].cmd[0], "env", 4) == 0
			|| ft_strncmp(data->cmd[index].cmd[0], "exit", 5) == 0)
			return (true);
	}
	return (false);
}

void	execute_builtins(t_data *data, char **env, int index)
{
	if (ft_strncmp(data->cmd[index].cmd[0], "echo", 5) == 0)
		ft_echo(data, index);
	else if (ft_strncmp(data->cmd[index].cmd[0], "cd", 3) == 0)
		ft_cd(data, index);
	else if (ft_strncmp(data->cmd[index].cmd[0], "pwd", 4) == 0)
		ft_pwd(data, index);
	else if (ft_strncmp(data->cmd[index].cmd[0], "export", 7) == 0)
		ft_export(data, env, index);
	else if (ft_strncmp(data->cmd[index].cmd[0], "unset", 6) == 0)
		ft_unset(data, index);
	else if (ft_strncmp(data->cmd[index].cmd[0], "env", 4) == 0)
		ft_env(data, env, index);
	else if (ft_strncmp(data->cmd[index].cmd[0], "exit", 5) == 0)
		ft_exit(data, index);
}

bool	builtin_in_parent(t_data *data, int i)
{
	if (data->cmd[i].cmd[0] != NULL)
	{
		if (data->cmd[i].status != 0 && is_parent_builtin (data, i) == true)
		{
			error_file_msg(data->cmd[i].error_str, data->cmd[i].msg_error);
			g_exit_status = 1;
			return (true);
		}
		else if (is_parent_builtin(data, i) == true)
			return (true);
	}
	return (false);
}
