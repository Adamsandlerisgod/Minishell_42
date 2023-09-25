/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:11 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/22 20:38:03 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/*
The function size_array_pipe returns the number of commands in the array.
It takes a t_cmd structure as parameter.
It returns the number of commands.
*/

static size_t	size_array_pipe(t_cmd *cmd, int index)
{
	size_t	i;

	i = 0;
	while (cmd[index + i].pipe == 1 && cmd[index + i].cmd != NULL)
		i++;
	return (i + 1);
}

/*
The function waitpid is used to wait for the child process to finish.
It takes an array of pid_t and the size of the array as parameters.
It returns the status of the last child process.
*/

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

/*
The function pipe_op is used to execute the commands separated by a pipe.
It takes a t_cmd structure, an environment variable array,
and an index as parameters.
It returns the status of the last child process.
*/

static void	pipe_op(t_data *data, char **ev, int *index)
{
	pid_t	*pid;
	size_t	len_array;

	len_array = size_array_pipe(data->cmd, index);
	if (len_array == 1 && (is_builtins(data->cmd[*index].cmd) == true))
		data->status = execute_builtins(data, index);
	else
	{
		pid = fork_process(len_array, data, ev, index);
		if (pid == NULL)
		return ;
		data->status = waiting_pid(len_array, pid);
	}
	*index += len_array;
}

/*
The function separator_op is the main function of the execution part.
It takes a t_cmd structure and an environment variable array as parameters,
and the size of the array.
It returns the exit status of the last command executed.
*/

int	separator_op(t_data *data, char **ev, int len)
{
	(void)len;
	data->status = 0; // to remove Wolf will initialize it
	pipe_op(data, ev, 0);
	return (WEXITSTATUS(data->status));
}
