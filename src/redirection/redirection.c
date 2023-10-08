/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:16:54 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/09 02:12:20 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	redirection_pipes(t_data *data, int index)
{
	if (data->cmd[index].pipe_in == true && data->cmd[index].file_in == false)
	{
		if (dup_files(data->pipefd[0], STDIN_FILENO) != CMD_OK)
			return (CMD_ERROR);
	}
	if (data->cmd[index].pipe_out == true && data->cmd[index].file_out == false)
	{
		if (dup_files(data->pipefd[1], STDOUT_FILENO) != CMD_OK)
			return (CMD_ERROR);
	}
	return (CMD_OK);
}

int	redirection_files(t_data *data, int index)
{
	if (data->cmd[index].file_in == true)
	{
		if (redir_infiles(data, index) != CMD_OK)
			exit (CMD_ERROR);
	}
	if (data->cmd[index].file_out == true)
	{
		if (redir_outfiles(data, index) != CMD_OK)
			exit (CMD_ERROR);
	}
	return (CMD_OK);
}

int	check_access_files(t_data *data, int index)
{
	int	i;

	i = 0;
	while (data->cmd[index].infiles[i] != NULL )
	{
		if (access(data->cmd[index].infiles[i], F_OK) == -1
			&& data->cmd[index].infiles[i] != NULL)
			return (error_system("file not found\n", errno), CMD_EXIT);
		else if (access(data->cmd[index].infiles[i], R_OK) == -1
			&& data->cmd[index].infiles[i] != NULL)
			return (error_system("permission denied\n", errno), CMD_EXIT);
	}
	i = 0;
	while (data->cmd[index].outfiles[i])
	{
		if (access(data->cmd[index].outfiles[i], W_OK) == -1)
			return (error_system("permission denied\n", errno), CMD_EXIT);
	}
	return (CMD_OK);
}

	//int	status;

	//status = CMD_OK;
	//if (data->cmd[index].in_redir == true || data->cmd[index].out_redir == true)
	//{
	//	if (open_files(data, index) != CMD_OK)
	//		status = CMD_ERROR;
	//}
	//if (data->cmd[index].pipe_in == true && data->cmd[index].in_redir == false)
	//{
	//	if (dup_files(data->pipefd[0], STDIN_FILENO) != CMD_OK)
	//		status = CMD_ERROR;
	//}
	//if (data->cmd[index].pipe_out == true
	//	&& data->cmd[index].out_redir == false)
	//{
	//	if (dup_files(data->pipefd[1], STDOUT_FILENO) != CMD_OK)
	//		status = CMD_ERROR;
	//}
	//return (status);
