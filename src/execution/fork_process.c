/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:17:02 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/06 12:41:27 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	child_process(t_data *data, char **env, int index)
{
	if (data->cmd[index].here_doc_in == true)
	{
		if (redirection_heredoc(data, index) != CMD_OK)
			exit(CMD_ERROR);
	}
	if (check_access_files(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (redirection_files(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (redirection_pipes(data, index) != CMD_OK)
		exit(CMD_ERROR);
	if (is_builtins(data, index) == true)
		exit(execute_builtins(data, env, index));
	else
		execute_cmd(data->cmd[index].cmd, env);
}

static void parent_process(t_data *data, int index)
{
	(void) index;
	close(data->pipefd[1]);
	// printf("INDEX %d \n", index);
	// printf("PIPE_OUT %d \n", data->cmd[index].pipe_out);
	// printf("PIPE_OUT %d \n", data->cmd[index].file_in);
	// printf("PIPE_OUT %d \n", data->cmd[index].here_doc_in);
	if (/*data->cmd[index].pipe_out == true &&*/ data->cmd[index].file_in == false
		&& data->cmd[index].here_doc_in == false)
	{
		// printf("DUP_FILES cmd %s \n", data->cmd[index].cmd[0]);
		dup_files(data->pipefd[0], STDIN_FILENO);
	}
	// printf("HERE STOP 01 \n");
	// printf("HERE STOP 02 \n");
	// dup_files(data->pipefdls[0], STDIN_FILENO);
	close(data->pipefd[0]);
	// printf("HERE STOP 03 \n");
}

pid_t	*fork_process(t_data *data, char **env, int index)
{
	pid_t	*pid;
	size_t	i;

	pid = (pid_t *)malloc(sizeof(pid_t) * data->pipe_len);
	if (!pid)
		return (error_system("malloc failed"), NULL);
	i = 0;
	printf("data->pipe_len => %zu\n", data->pipe_len);
	while (i < data->pipe_len)
	{
		printf("CMD => %s \n", data->cmd[index + i].cmd[0]);
		if (pipe(data->pipefd) == -1)
			return (error_system("pipe failed"), NULL);
		pid[i] = fork();
		if (pid[i] == -1)
			return (error_system("fork failed"), NULL);
		else if (pid[i] == 0)
		{
			child_process(data, env, index + i);
			// printf("SOMETHING HERE ??? child_process \n");
		}
		else if (pid[i] > 0)
		{
			parent_process(data, index + i);
			// printf("SOMETHING HERE ??? parent_process \n");
		}
		i++;
		// printf("END OF LOOP fork_process \n");
	}
	return (pid);
}
