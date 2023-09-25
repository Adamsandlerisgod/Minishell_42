/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:17:02 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/22 13:17:03 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/*
The function creat_here_doc() creates a file named "here_doc" and writes
the input of the user in it.
It takes as parameters:
	- limiter: the limiter of the here_doc
It returns nothing.
*/

static int	creat_here_doc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ((ft_strlen(line) - 1) == ft_strlen(limiter)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (fd);
}

/*
The function open_infile() opens the input file.
It takes as parameters:
	- infile: the input file
	- here_doc: a boolean to know if the input file is a here_doc
	- limiter: the limiter of the here_doc
It returns nothing.
*/

static int	open_infile(char *infile, bool here_doc, char *limiter, bool in_redir)
{
	int	fd_in;
	int	tmpfd[2];
	int	status;

	status = 0;
	if (here_doc == true)
		fd_in = creat_here_doc(limiter);
	else
		fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		return (msg_cmd(infile, "open failed."), -1);
	if (fd_in == -1 && in_redir == true)
	{
		if (pipe(tmpfd) == -1)
			return (msg_cmd("pipe", "pipe failed."), -1);
		if (dup2(tmpfd[0], STDIN_FILENO) == -1)
			return (msg_cmd("dup2", "dup2 failed."), -1);
		close(tmpfd[0]);
		close(tmpfd[1]);
	}
	else
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			return (msg_cmd("dup2", "dup2 failed."), -1);
		close(fd_in);
	}
	return (status);
}

/*
The function pipe_process() creates a pipe for each command.
It takes as parameters:
	- cmd: the commands
	- pipefd: the pipe file descriptors
	- index: the index of the current command
It returns nothing.
*/

static int	pipe_process(t_cmd *cmd, int pipefd[2], int i)
{
	int	status;

	if (pipe(pipefd) == -1)
		return (msg_cmd("pipe", "pipe failed."), -1);
	if (cmd[i].out_redir == true)
		status = open_infile(cmd[i].infile, cmd[i].here_doc,
			cmd[i].limiter, cmd[i].in_redir);
	return (status);
}

/*
The fork_process() function creates a child process for each command.
The parent process will execute the next command.
The child process will execute the current command.
It takes as parameters:
	- len: the number of commands
	- cmd: the commands
	- ev: the environment variables
It returns an array of pid_t containing the pid of each child process.
*/

pid_t	*fork_process(size_t len, t_data *data, char **ev, int index)
{
	pid_t	*pid;
	int		pipefd[2];
	size_t	i;

	pid = (pid_t *)malloc(sizeof(pid_t) * len);
	if (!pid)
		return (msg_cmd("malloc", "allocation for pid failed."), NULL);
	i = 0;
	while (i < len)
	{
		pipe_process(data->cmd, pipefd, index + i);
		pid[i] = fork();
		if (pid[i] == -1)
			msg_cmd("fork", "fork failed.");
		else if (pid[i] == 0)
			child_process(pipefd, data->cmd, ev, index + i);
		else if (pid[i] > 0)
			parent_process(data, pipefd, len);
		i++;
	}
	return (pid);
}
