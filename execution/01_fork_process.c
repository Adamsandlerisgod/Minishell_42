/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_fork_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:54:22 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 02:40:04 by jhurpy           ###   ########.fr       */
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
		exit_error("minishell: ", "here_doc");
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

static void	open_infile(char *infile, bool here_doc, char *limiter)
{
	int	fd_in;
	int	tmpfd[2];

	if (here_doc == true)
		fd_in = creat_here_doc(limiter);
	else
		fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		perror("minishell");
	if ((access(infile, R_OK) == -1 && access(infile, F_OK) == 0)
		|| access(infile, F_OK) == -1 || fd_in == -1)
	{
		if (pipe(tmpfd) == -1)
			exit_error("minishell: ", "pipe failed ");
		if (dup2(tmpfd[0], STDIN_FILENO) == -1)
			exit_error("minishell: ", "dup2 failed ");
		close(tmpfd[0]);
		close(tmpfd[1]);
	}
	else
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			exit_error("minishell: ", "dup2 failed ");
		close(fd_in);
	}
}

/*
The function pipe_process() creates a pipe for each command.
It takes as parameters:
	- cmd: the commands
	- pipefd: the pipe file descriptors
	- index: the index of the current command
It returns nothing.
*/

static void	pipe_process(t_cmd *cmd, int pipefd[2], int i, int index)
{
	if (pipe(pipefd) == -1)
		exit_error("minishell: ", "pipe failed ");
	if (i == 0)
		open_infile(cmd[index + i].infile, cmd[index + i].here_doc,
			cmd[index + i].limiter);
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
		exit_error("minishell: malloc failed", NULL);
	i = 0;
	while (i < len)
	{
		pipe_process(data->cmd, pipefd, i, index);
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error("minishell: fork failed", NULL);
		else if (pid[i] == 0)
			child_process(pipefd, data->cmd, ev, index + i);
		else if (pid[i] > 0)
			parent_process(data, pipefd);
		i++;
	}
	return (pid);
}
