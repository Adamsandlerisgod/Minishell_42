/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_separator_op_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 09:52:27 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 02:39:09 by jhurpy           ###   ########.fr       */
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

static int	pipe_op(t_data *data, char **ev, int *index)
{
	pid_t	*pid;
	size_t	len_array;
	int		status;

	len_array = size_array_pipe(data->cmd, index);
	pid = fork_process(len_array, data, ev, index);
	status = waiting_pid(len_array, pid);
	*index += len_array;
	return (status);
}

/*
The function separator_op_bonus is the main function of the execution part.
It takes a t_cmd structure and an environment variable array as parameters,
and the size of the array.
It returns the exit status of the last command executed.
*/

int	separator_op(t_data *data, char **ev, int len)
{
	int		status;
	int		i;

	i = 0;
	status = 0;
	while (i < len)
	{
		if (data->cmd[i].op == true && status == 0)
			status = pipe_op(data, ev, &i);
		else if (data->cmd[i].op == false && status != 0)
			status = pipe_op(data, ev, &i);
		else
			i++;
	}
	//if (ft_strncmp("here_doc", av[1], 9) == 0)
	//	unlink("here_doc");
	return (WEXITSTATUS(status));
}
