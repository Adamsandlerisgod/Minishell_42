/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:16:54 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 15:52:56 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	dup_files(int fd_origin, int fd_target)
{
	if (dup2(fd_origin, fd_target) == -1)
	{
		error_system("dup2 failed\n", errno);
		return (CMD_ERROR);
	}
	return (CMD_OK);
}

int	redirection(t_data *data, int index)
{
	int	status;

	status = CMD_OK;
	if (pipe(data->pipefd) == -1)
		return (error_system("pipe failed\n", errno), CMD_ERROR);
	if (data->cmd[index].in_redir == true || data->cmd[index].out_redir == true)
	{
		if (open_files(data, index) != CMD_OK)
			status = CMD_ERROR;
	}
	if (data->cmd[index].pipe_in == true && data->cmd[index].in_redir == false)
	{
		if (dup_files(data->pipefd[0], STDIN_FILENO) != CMD_OK)
			status = CMD_ERROR;
	}
	if (data->cmd[index].pipe_out == true
		&& data->cmd[index].out_redir == false)
	{
		if (dup_files(data->pipefd[1], STDOUT_FILENO) != CMD_OK)
			status = CMD_ERROR;
	}
	return (status);
}
