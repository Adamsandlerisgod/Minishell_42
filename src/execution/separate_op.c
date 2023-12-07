/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:11 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/07 15:46:53 by whendrik         ###   ########.fr       */
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

// static size_t	size_array_pipe(t_cmd *cmd, int index)
// {
// 	size_t	i;

// 	i = 0;
// 	while (cmd[index].cmd != NULL)
// 	{
// 		index++;
// 		i++;
// 		printf("i++ => %zu \n", i);
// 		// printf("size_array_pipe cmd[index].cmd = %s", cmd[index].cmd[0]);
// 	}
// 	return (i);
// }

static int	waiting_pid(size_t len, pid_t *pid)
{
	int		status;
	size_t	i;

	i = 0;
	while (i < len)
		waitpid(pid[i++], &status, WUNTRACED);
	free(pid);
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
		status = waiting_pid(data->pipe_len, pid_array);
	}
	// else if (pid > 0)
	printf("waitpid for how long \n");
	waitpid(pid, &data->status, WUNTRACED);
}

static int	pipe_op(t_data *data, char **env, int index)
{
	// data->pipe_len = size_array_pipe(data->cmd, index);
	open_heredoc(data);
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

	printf("===>>> separator_op 00 <<<===\n");
	data->status = CMD_OK;
	printf("===>>> separator_op 01 <<<===\n");
	
	ev = env_array(data->env);
	printf("===>>> separator_op 02 <<<===\n");

	if (ev == NULL)
		return (CMD_ERROR);
	printf("===>>> separator_op 03 <<<===\n");
	
	if (pipe_op(data, ev, 0) != CMD_OK)
		return (CMD_ERROR);
	printf("===>>> separator_op 04 <<<===\n");

	free_array(ev);
	printf("===>>> separator_op 05 <<<===\n");
	return (WEXITSTATUS(data->status));
}
