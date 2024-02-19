/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 22:45:18 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 15:03:55 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_error_exit(t_data *data, int index)
{
	DIR		*dir;

	if (data->cmd[index].status != 0 || (data->cmd[index].status == 0
			&& data->cmd[index].cmd[0] == NULL)
		|| ft_strlen(data->cmd[index].cmd[0]) == 0)
	{
		if (ft_strlen(data->cmd[index].cmd[0]) == 0)
		{
			error_cmd(data->cmd[index].cmd[0], NO_CMD);
			exit(CMD_NOT_FOUND);
		}
		else if (data->cmd[index].error_str != NULL
			|| data->cmd[index].msg_error != NULL)
			error_cmd(data->cmd[index].error_str, data->cmd[index].msg_error);
		exit (data->cmd[index].status);
	}
	dir = opendir(data->cmd[index].cmd[0]);
	if (dir != NULL)
	{
		error_cmd(data->cmd[index].cmd[0], IS_DIR);
		closedir(dir);
		exit (CMD_NOT_EXEC);
	}
}

static void	files_redirection(t_data *data, int index)
{
	if (data->cmd[index].fd_infile > 2)
	{
		dup2(data->cmd[index].fd_infile, STDIN_FILENO);
		close(data->cmd[index].fd_infile);
		if (data->cmd[index].here_doc_fd > 2)
			close(data->cmd[index].here_doc_fd);
	}
	if (data->cmd[index].fd_outfile > 2)
	{
		dup2(data->cmd[index].fd_outfile, STDOUT_FILENO);
		close(data->cmd[index].fd_outfile);
	}
}

static int	redirection_pipes(t_data *data, int index)
{
	close(data->pipefd[0]);
	if (data->cmd[index].pipe_out == true && data->cmd[index].fd_outfile < 2)
		dup2(data->pipefd[1], STDOUT_FILENO);
	close(data->pipefd[1]);
	return (CMD_OK);
}

void	child_process(t_data *data, char **env, int index)
{
	check_error_exit(data, index);
	if (data->cmd[index].fd_infile > -1 || data->cmd[index].fd_outfile > 2)
		files_redirection(data, index);
	if (data->cmd[index].status == 0 && data->pipe_len > 1)
		redirection_pipes(data, index);
	open_quit_signal_on_valid_cmd(data, index);
	if (is_builtins(data, index) == true)
	{
		execute_builtins(data, env, index);
		exit (g_exit_status);
	}
	else if (execve(data->cmd[index].path, data->cmd[index].cmd, env) == -1)
	{
		error_system("execve failed");
		exit (CMD_ERROR);
	}
}
