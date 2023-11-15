/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_outfiles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:11:14 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/07 17:43:22 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	open_outfile(char *outfile, bool append)
{
	int	fd_out;
	int	status;
	int w_mode;

	if (append == true)
		w_mode = O_APPEND;
	else
		w_mode = O_TRUNC;
	status = CMD_OK;
	fd_out = open(outfile, O_WRONLY | O_CREAT | w_mode, 0644);
	if (fd_out == -1)
	{
		error_system("open failed");
		status = CMD_ERROR;
	}
	else
	{
		status = dup_files(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
	return (status);
}

int	redir_outfiles(t_data *data, int index)
{
	int	i;
	int	status;

	i = 0;
	status = CMD_OK;
	if (data->cmd[index].file_out == true)
	{
		while (data->cmd[index].outfiles[i + 1] != NULL)
			i++;
		status = open_outfile(data->cmd[index].outfiles[i],
				data->cmd[index].append);
	}
	return (status);
}
