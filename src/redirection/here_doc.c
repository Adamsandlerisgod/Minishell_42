/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:04:25 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 23:52:47 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	creat_here_doc(t_data *data, int index, int i_file, bool flag)
{
	char	*line;
	int		tmp_pipe[2];

	pipe(tmp_pipe);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, data->cmd[index].limiters[i_file],
				ft_strlen(data->cmd[index].limiters[i_file])) == 0
			&& ((ft_strlen(line) - 1)
				== ft_strlen(data->cmd[index].limiters[i_file])))
			break ;
		if (flag == true)
			write(data->pipefd[1], line, ft_strlen(line));
		else
			write(tmp_pipe[1], line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	close (tmp_pipe[1]);
	close (tmp_pipe[0]);
}

static void	execute_heredoc(t_data *data, int i)
{
	int		j;
	bool	flag;

	flag = false;
	j = 0;
	while (data->cmd[i].nb_heredocs > j)
	{
		if (data->cmd[i].here_doc_in == true
			&& data->cmd[i].nb_heredocs == j + 1)
			flag = true;
		creat_here_doc(data, i, j, flag);
		if (flag == true)
			break ;
		j++;
	}
	exit (g_exit_status);
}

static void	get_exit_status(void)
{
	if (g_exit_status == 33280)
		g_exit_status = 1;
	else
		g_exit_status = 0;
}

static void	fork_heredoc(t_data *data, pid_t *pid, size_t i)
{
	pid = (pid_t *)malloc(sizeof(pid_t) * data->pipe_len);
	while (i < data->pipe_len && g_exit_status == 0)
	{
		pipe(data->pipefd);
		pid[i] = fork();
		if (pid[i] == -1)
			error_system(FORK_ERROR);
		else if (pid[i] == 0)
		{
			data->sa_i.sa_handler = sigint_child_handler;
			sigaction(SIGINT, &data->sa_i, NULL);
			execute_heredoc(data, i);
		}
		else if (pid[i] > 0)
		{
			waitpid(pid[i], &g_exit_status, 0);
			close(data->pipefd[1]);
			data->cmd[i].here_doc_fd = dup(data->pipefd[0]);
			close(data->pipefd[0]);
		}
		i++;
	}
	free(pid);
}

bool	open_heredoc(t_data *data)
{
	size_t	i;
	bool	flag;
	pid_t	*pid;

	i = 0;
	flag = false;
	pid = NULL;
	set_signal(data, IGNORE_SIGINT_PARENT);
	while (data->pipe_len > i)
	{
		if (data->cmd[i++].here_doc_in == true)
		{
			flag = true;
			g_exit_status = 0;
		}
	}
	if (flag == true)
		fork_heredoc(data, pid, 0);
	get_exit_status();
	set_signal(data, HANDLE_SIGINT_PARENT);
	return (flag);
}
