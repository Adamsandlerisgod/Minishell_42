/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:57:28 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/28 15:45:05 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	open_infile(char *infile, bool here_doc, char *limiter, bool in_redir)
{
	int	fd_in;
	int	tmpfd[2];
	int	status;

	status = CMD_OK;
	if (here_doc == true)
		fd_in = creat_here_doc(limiter);
	else
		fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
	{
		if (pipe(tmpfd) == -1)
			// Error message management; pipe failed
		dup_files(STDIN_FILENO, tmpfd[0]);
		status = CMD_ERROR;
	}
	else
		status = dup_files(fd_in, STDIN_FILENO);
	return (status);
}

static int	open_outfile(char *outfile, int w_mode)
{
	int	fd_out;
	int	status;

	status = CMD_OK;
	if (access(outfile, W_OK) == -1)
	{
		// Error message management; permission denied
		status = CMD_EXIT;
	}
	else
	{
		fd_out = open(outfile, O_WRONLY | O_CREAT | w_mode, 0644);
		if (fd_out == -1)
		{
			// Error message management; open failed
			status = CMD_ERROR;
		}
	}
	status = dup_files(fd_out, STDOUT_FILENO);
	close(fd_out);
	return (status);
}


int	open_files(t_data *data, int index)
{
	int	status;

	status = CMD_OK;
	if (data->cmd[index].in_redir == true)
		status = open_infile (data->cmd[index].infile, data->cmd[index].here_doc,
			data->cmd[index].limiter, data->cmd[index].in_redir);
	else if (data->cmd[index].out_redir == true)
		status = open_outfile(data->cmd[index].outfile, data->cmd[index].w_mode);
	return (status);
}
