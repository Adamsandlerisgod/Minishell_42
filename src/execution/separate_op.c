/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:11 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/05 21:01:11 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static size_t	size_array_pipe(t_cmd *cmd, int index)
{
	size_t	i;

	i = 0;
	while (cmd[index + i].pipe_in == true && cmd[index + i].cmd != NULL)
		i++;
	return (i + 1);
}

static int	waiting_pid(size_t len, pid_t *pid)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < len)
		waitpid(pid[i++], &status, WUNTRACED);
	free(pid);
	return (status);
}

static int	pipe_op(t_data *data, char **env, int *index)
{
	pid_t	*pid;

	data->pipe_len = size_array_pipe(data->cmd, index);
	if (builtin_in_parent(data, env, index) == true)
		return (CMD_OK);
	else
	{
		pid = fork_process(data, env, index);
		if (pid == NULL)
			return (CMD_ERROR);
		data->status = waiting_pid(data->pipe_len, pid);
	}
	return (CMD_OK);
}

/*
The function separator_op is used to execute a list of pipe command.
It returns the status of the last command executed.
*/

int	separator_op(t_data *data)
{
	char	**env;

	data->status = CMD_OK;
	env = env_array(data->env);
	if (env == NULL)
		return (CMD_ERROR);
	if (pipe_op(data, env, 0) != CMD_OK)
		return (CMD_ERROR);
	free_array(env);
	return (WEXITSTATUS(data->status));
}
