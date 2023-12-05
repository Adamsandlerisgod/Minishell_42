/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:16:54 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/05 23:44:18 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_heredoc(t_data *data, int index)
{
	// printf("redirection_heredoc \n");
	if (data->cmd[index].here_doc_in == true)
	{
		if (dup_files(data->cmd[index].here_doc_fd, STDIN_FILENO) != CMD_OK)
			return (CMD_ERROR);
		else
			return (close (data->cmd[index].here_doc_fd), CMD_OK);
	}
	return (CMD_OK);
}

int	redirection_pipes(t_data *data, int index)
{	
	// printf("redirection_pipes \n");
	if (data->cmd[index].pipe_out == true && data->cmd[index].file_out == false)
	{
		// printf("redirection_pipes 01\n");
		if (dup_files(data->pipefd[1], STDOUT_FILENO) != CMD_OK)
			return (CMD_ERROR);
	}
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	return (CMD_OK);
}

int	redirection_files(t_data *data, int index)
{
	// printf("redirection_files \n");
	if (data->cmd[index].file_in == true)
	{
		// printf("redirection_files 01\n");
		if (redir_infiles(data, index) != CMD_OK)
			exit (CMD_ERROR);
	}
	if (data->cmd[index].file_out == true)
	{
		// printf("redirection_files 02\n");
		if (redir_outfiles(data, index) != CMD_OK)
			exit (CMD_ERROR);
	}
	return (CMD_OK);
}

static int	creat_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (error_system("open error"), CMD_ERROR);
	close(fd);
	return (CMD_OK);
}


int	check_access_files(t_data *data, int index)
{
	int	i;

	i = 0;
	// printf("check_access_files \n");
	while (data->cmd[index].infiles[i] != NULL)
	{
		// printf("check_access_files 01\n");
		if (access(data->cmd[index].infiles[i], F_OK) == -1
			&& data->cmd[index].infiles[i] != NULL)
			return (error_system("file not found"), CMD_EXIT);
		else if (access(data->cmd[index].infiles[i], R_OK) == -1
			&& data->cmd[index].infiles[i] != NULL)
			return (error_system("permission denied"), CMD_EXIT);
		i++;
	}
	i = 0;
	while (data->cmd[index].outfiles[i] != NULL)
	{
		// printf("check_access_files 02\n");
		if (access(data->cmd[index].outfiles[i], F_OK) == -1)
		{
			if (creat_outfile(data->cmd[index].outfiles[i]) != CMD_OK)
				return (CMD_ERROR);
		}
		if (access(data->cmd[index].outfiles[i], W_OK) == -1)
			return (error_system("permission denied"), CMD_EXIT);
		i++;
	}
	return (CMD_OK);
}
