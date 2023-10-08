/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:04:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/07 16:25:13 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	creat_here_doc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ((ft_strlen(line) - 1) == ft_strlen(limiter)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (fd);
}

static int	check_exist_heredoc(void)
{
	if (access(HEREDOC_NAME, F_OK) == 0)
	{
		if (unlink(HEREDOC_NAME) == -1)
			return (error_system("unlink failed\n", errno), CMD_ERROR);
	}
	return (CMD_OK);
}

int	execute_heredoc(t_data *data, int index)
{
	int		i;
	int		fd;

	i = 0;
	fd = -1;
	while (data->cmd[index].nb_heredocs > i)
	{
		if (check_exist_heredoc() != CMD_OK)
			return (CMD_ERROR);
		if (fd != -1)
			close(fd);
		fd = creat_here_doc(data->cmd[index].limiters[i]);
		if (fd == -1)
			return (error_system("create heredoc failed\n", errno), CMD_ERROR);
		i++;
	}
	if (data->cmd[index].here_doc_in == true)
	{
		if (dup_files(fd, STDIN_FILENO) != CMD_OK)
			return (CMD_ERROR);
	}
	close(fd);
	unlink(HEREDOC_NAME);
	return (CMD_OK);
}
