/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_child_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:04:24 by jhurpy            #+#    #+#             */
/*   Updated: 2023/08/30 01:55:04 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/*
The function open_outfile() opens the output file.
It takes as parameters:
	- outfile: the output file
	- append: a boolean to know if the output file is append
It returns nothing.
*/

static void	open_outfile(char *outfile, bool append)
{
	int	fd_out;

	fd_out = 0;
	if (append == true)
	{
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out == -1)
		{
			perror("pipex");
			exit(EXIT_FAILURE);
		}
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit_error("pipex: ", "dup2 failed ");
	close(fd_out);
}

/*
The function child_process() executes the command in the child process.
It takes as parameters:
	- pipefd: the pipe file descriptor
	- cmd: the command structure
	- ev: the environment variables
	- index: the index of the command in the command structure
It returns nothing.
*/

void	child_process(int pipefd[2], t_cmd *cmd, char **ev, int index)
{
	if (cmd[index + 1].cmd == NULL)
		open_outfile(cmd[index].outfile, cmd[index].append);
	else
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit_error("pipex: ", "dup2 failed ");
	}
	close(pipefd[0]);
	close(pipefd[1]);
	// insert if condition with execute_cmd for builtins
	execute_cmd(cmd[index].cmd, ev);
}
