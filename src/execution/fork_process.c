/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:17:02 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 00:02:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	child_process(t_data *data, char **env, int index)
{
	if (check_builtins(data->cmd[index].cmd[0]) == true)
		execute_builtins(data->cmd, env, index);
	else
		execute_cmd(data->cmd[index].cmd, env);
}

static int	parent_process(int pipefd[2])
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		// Error message management; dup2 failed
		close(pipefd[0]);
		return (CMD_ERROR);
	}
	close(pipefd[0]);
	return (CMD_OK);
}

/*
The function fork_process is used to create a list of child process.
It returns a list of pid.
*/

pid_t	*fork_process(t_data *data, char **env, int index)
{
	pid_t	*pid;
	size_t	i;
	int		pipefd[2];

	pid = (pid_t *)malloc(sizeof(pid_t) * data->pipe_len);
	if (!pid)
	{
		// Error message management; malloc failed
		return (CMD_ERROR);
	}
	i = 0;
	while (i < data->pipe_len)
	{
		if (redirection(data, pipefd, index + i) == CMD_ERROR);
			return (CMD_ERROR);
		pid[i] = fork();
		if (pid[i] == -1)
		{
			// Error message management; fork failed
			return (CMD_ERROR);
		}
		else if (pid[i] == 0)
			child_process(data, env, index + i);
		else if (pid[i] > 0)
			parent_process(pipefd);
		i++;
	}
	return (pid);
}
