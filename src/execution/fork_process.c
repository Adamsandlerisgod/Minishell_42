/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:17:02 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/09 02:12:34 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	child_process(t_data *data, char **env, int index)
{
	if (execute_heredoc(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (check_access_files(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (redirection_files(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (redirection_pipes(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (check_builtins(data->cmd[index].cmd[0]) == true)
		exit(execute_builtins(data->cmd, env, index));
	else
		execute_cmd(data->cmd[index].cmd, env);
}

pid_t	fork_process(t_data *data, char **env, int index)
{
	pid_t	*pid;
	size_t	i;

	pid = (pid_t *)malloc(sizeof(pid_t) * data->pipe_len);
	if (!pid)
		return (error_system("malloc failed\n", errno), CMD_ERROR);
	i = 0;
	while (i < data->pipe_len)
	{
		if (pipe(data->pipefd) == -1)
			return (error_system("pipe failed\n", errno), CMD_ERROR);
		pid[i] = fork();
		if (pid[i] == -1)
			return (error_system("fork failed\n", errno), CMD_ERROR);
		else if (pid[i] == 0)
			child_process(data, env, index + i);
		else if (pid[i] > 0)
		{
			close(data->pipefd[0]);
			close(data->pipefd[1]);
		}
		i++;
	}
	return (pid);
}
