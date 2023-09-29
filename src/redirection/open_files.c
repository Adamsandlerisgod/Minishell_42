/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:57:28 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 16:17:49 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	check_access_files(char *files, int flag)
{
	if (flag == 1)
	{
		if (access(files, R_OK) == -1)
			return (error_cmd(files, "Permission denied\n"), CMD_ERROR);
	}
	else
	{
		if (access(files, W_OK) == -1)
			return (error_cmd(files, "Permission denied\n"), CMD_ERROR);
	}
	return (CMD_OK);
}

int	open_here_doc(t_data *data, int index)
{
	int	fd_in;
	int	tmpfd[2];
	int	status;

	status = CMD_OK;
	fd_in = creat_here_doc(data->cmd[index].limiter);
	if (fd_in == -1)
	{
		if (pipe(tmpfd) == -1)
			error_system("pipe failed\n", errno);
		dup_files(STDIN_FILENO, tmpfd[0]);
		status = CMD_ERROR;
	}
	else
	{
		status = dup_files(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	return (status);
}

int	open_infile(t_data *data, int index)
{
	int	fd_in;
	int	tmpfd[2];
	int	status;

	status = CMD_OK;
	if (check_access_files(data->cmd[index].infile, 1) == CMD_OK)
		fd_in = open(data->cmd[index].infile, O_RDONLY);
	else
		fd_in = -1;
	if (fd_in == -1)
	{
		if (pipe(tmpfd) == -1)
			error_system("pipe failed\n", errno);
		dup_files(STDIN_FILENO, tmpfd[0]);
		status = CMD_ERROR;
	}
	else
	{
		status = dup_files(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	return (status);
}

static int	open_outfile(t_data *data, int index)
{
	int	fd_out;
	int	status;

	status = CMD_OK;
	status = check_access_files(data->cmd[index].outfile, 2);
	if (status == CMD_OK)
	{
		fd_out = open(data->cmd[index].outfile, O_WRONLY
				| O_CREAT | data->cmd[index].w_mode, 0644);
		if (fd_out == -1)
		{
			error_system("open failed\n", errno);
			status = CMD_ERROR;
		}
		else
		{
			status = dup_files(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}
	return (status);
}

int	open_files(t_data *data, int index)
{
	int	status;

	status = CMD_OK;
	if (data->cmd[index].here_doc == true && data->cmd[index].in_redir == true)
		status = open_here_doc(data, index);
	else if (data->cmd[index].in_redir == true
		&& data->cmd[index].here_doc == false)
		status = open_infile (data, index);
	if (data->cmd[index].out_redir == true)
		status = open_outfile(data, index);
	return (status);
}
