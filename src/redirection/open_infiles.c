/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_infiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:11:22 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/09 01:58:27 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	open_infile(char *infile)
{
	int	fd_in;
	int	tmpfd[2];
	int	status;

	status = CMD_OK;
	fd_in = open(infile, O_RDONLY);
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

int	redir_infiles(t_data *data, int index)
{
	int	i;
	int	status;

	i = 0;
	status = CMD_OK;
	if (data->cmd[index].file_in == true)
	{
		while (data->cmd[index].infiles[i + 1] != NULL)
			i++;
		status = open_infile(data->cmd[index].infiles[i]);
	}
	return (status);
}
