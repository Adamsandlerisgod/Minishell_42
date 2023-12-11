/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:11 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/11 22:40:33 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static int	waiting_pid(t_data *data, size_t len, pid_t *pid)
{
	int		status;
	size_t	i;

	(void) data;
	i = 0;
	while (i < len)
		waitpid(pid[i++], &status, WUNTRACED);
	free(pid);
	printf("HERE waiting_pid %d \n", status);
	exit (status);
}

static void	capsule_pipe(t_data *data, char **env, int index)
{
	int		status;
	pid_t	*pid_array;
	pid_t	pid;

	status = CMD_OK;
	pid = fork();
	if (pid == -1)
		error_system("fork failed");
	else if (pid == 0)
	{
		pid_array = fork_process(data, env, index);
		if (pid_array == NULL)
			exit(CMD_EXIT) ;
		status = waiting_pid(data, data->pipe_len, pid_array);
	}
	printf("HERE capsule_pipe %d \n", status);
	waitpid(pid, &data->status, WUNTRACED);
	// printf("HERE capsule_pipe %d \n", data->status);
}

static int	pipe_op(t_data *data, char **env, int index)
{
	open_heredoc(data);
	if (data->cmd[0].cmd[0] == NULL && data->pipe_len <= 1) /*NOT 100% SURE*/
		return (CMD_OK);
	if (builtin_in_parent(data, env, index) == true)
		return (CMD_OK);
	else
		capsule_pipe(data, env, index);
	return (CMD_OK);
}

/*
The function separator_op is used to execute a list of pipe command.
It returns the status of the last command executed.
*/

int	separator_op(t_data *data)
{
	char	**ev;

	data->status = CMD_OK;
	ev = env_array(data->env);
	if (ev == NULL)
		return (CMD_ERROR);
	if (pipe_op(data, ev, 0) != CMD_OK)
		return (CMD_ERROR);
	free_array(ev);
	return (WEXITSTATUS(data->status));
}
