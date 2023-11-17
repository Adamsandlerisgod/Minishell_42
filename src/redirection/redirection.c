/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 20:16:54 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/16 16:25:10 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirection_heredoc(t_data *data, int index)
{
	printf("Inshallah we in herdoc redirection \n");
	if (data->cmd[index].here_doc_in == true)
	{
		printf("heredoc fd [%d] = [%d] \n", index, data->cmd[index].here_doc_fd);
		if (dup_files(data->cmd[index].here_doc_fd, STDIN_FILENO) != CMD_OK)
			return (CMD_ERROR);
		else
			return (close (data->cmd[index].here_doc_fd), CMD_OK);
	}
	printf("Inshallah we still in herdoc redirection \n");
	return (CMD_OK);
}

int	redirection_pipes(t_data *data, int index)
{
	if (data->cmd[index].pipe_in == true && data->cmd[index].file_in == false
		&& data->cmd[index].here_doc_in == false)
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
	printf("check access files i++? 1 | index = %d | infile = %s\n", index, "africa");
	while (data->cmd[index].infiles[i] != NULL)
	{
		printf("yallah \n");
		if (access(data->cmd[index].infiles[i], F_OK) == -1
			&& data->cmd[index].infiles[i] != NULL)
			return (error_system("file not found"), CMD_EXIT);
		else if (access(data->cmd[index].infiles[i], R_OK) == -1
			&& data->cmd[index].infiles[i] != NULL)
			return (error_system("permission denied"), CMD_EXIT);
		printf("yallah 2 \n");
		i++;
	}
	printf("check access files i++? 2\n");
	i = 0;
	while (data->cmd[index].outfiles[i])
	{
		if (access(data->cmd[index].outfiles[i], F_OK) == -1)
		{
			if (creat_outfile(data->cmd[index].outfiles[i]) != CMD_OK)
				return (CMD_ERROR);
		}
		if (access(data->cmd[index].outfiles[i], W_OK) == -1)
			return (error_system("permission denied"), CMD_EXIT);
		i++;
	}
	printf("check access files i++? 3\n");
	return (CMD_OK);
}
