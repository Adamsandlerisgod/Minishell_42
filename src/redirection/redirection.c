/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:16:54 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/28 15:45:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	dup_files(int fd_origin, int fd_target)
{
	if (dup2(fd_origin, fd_target) == -1)
	{
		// Error message management; dup2 failed
		return (CMD_ERROR);
	}
	return (CMD_OK);
}

int	redirection(t_data *data, int *pipefd, int index)
{
	int	status;

	status = CMD_OK;
	if (data->cmd[index].in_redir == true || data->cmd[index].out_redir == true)
	{
		if (open_files(data, index) != CMD_OK)
			status = CMD_ERROR;
	}
	if (index != 0 && data->cmd[index].in_redir == false)
	{
		if (dup_files(pipefd[0], STDIN_FILENO) != CMD_OK)
			status = CMD_ERROR;
	}
	if (data->cmd[index].pipe == true && data->cmd[index].out_redir == false)
	{
		if (dup_files(pipefd[1], STDOUT_FILENO) != CMD_OK)
			status = CMD_ERROR;
	}
	return (status);
}
