/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:17:02 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 14:48:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parent_process(t_data *data, int index)
{
	(void)index;
	close(data->pipefd[1]);
	dup2(data->pipefd[0], STDIN_FILENO);
	close(data->pipefd[0]);
}

pid_t	*fork_process(t_data *data, char **env, int index)
{
	pid_t	*pid;
	size_t	i;

	pid = (pid_t *)malloc(sizeof(pid_t) * data->pipe_len);
	if (!pid)
		return (error_system(MALLOC_ERROR), NULL);
	i = 0;
	while (i < data->pipe_len)
	{
		if (pipe(data->pipefd) == -1)
			return (error_system(PIPE_ERROR), NULL);
		pid[i] = fork();
		if (pid[i] == -1)
			return (error_system(FORK_ERROR), NULL);
		else if (pid[i] == 0)
		{
			data->sa_i.sa_handler = sigint_child_handler;
			sigaction(SIGINT, &data->sa_i, NULL);
			child_process(data, env, index + i);
		}
		else if (pid[i] > 0)
			parent_process(data, index + i);
		i++;
	}
	return (pid);
}
