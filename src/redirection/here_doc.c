/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:04:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/16 15:49:21 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	creat_here_doc(t_data *data, int index, int i_file)
{
	char	*line;

	if (pipe(data->pipefd) == -1)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, data->cmd[index].limiters[i_file],
			ft_strlen(data->cmd[index].limiters[i_file])) == 0
			&& ((ft_strlen(line) - 1)
			== ft_strlen(data->cmd[index].limiters[i_file])))
			break ;
		write(data->pipefd[0], line, ft_strlen(line));
		free(line);
	}
	free(line);
	return (data->pipefd[0]);
}

void	open_heredoc(t_data *data)
{
	size_t	i;
	int		j;
	int		fd;

	i = 0;
	while (data->pipe_len > i)
	{
		j = 0;
		while (data->cmd[i].nb_heredocs > j)
		{
			fd = creat_here_doc(data, i, j);
			j++;
			if (data->cmd[i].here_doc_in == true && data->cmd[i].nb_heredocs == j)
				data->cmd[i].here_doc_fd = dup(fd);
			close(fd);
		}
		i++;
	}
}

//static char	*creat_name_file(void)
//{
//	char	*name;
//	char	*tmp;
//	int		i;

//	i = 0;
//	name = ft_strdup(HEREDOC_NAME);
//	while (access(name, F_OK) == 0)
//	{
//		free(name);
//		tmp = ft_itoa(i);
//		name = ft_strjoin(HEREDOC_NAME, tmp);
//		free(tmp);
//		i++;
//	}
//	return (name);
//}

//static int	creat_here_doc(char *limiter)
//{
//	char	*line;
//	int		fd;

//	fd = open(creat_name_file(), O_CREAT | O_RDWR | O_TRUNC, 0644);
//	if (fd == -1)
//		return (-1);
//	while (1)
//	{
//		write(STDOUT_FILENO, "> ", 2);
//		line = get_next_line(STDIN_FILENO);
//		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
//			&& ((ft_strlen(line) - 1) == ft_strlen(limiter)))
//			break ;
//		write(fd, line, ft_strlen(line));
//		free(line);
//	}
//	free(line);
//	return (fd);
//}

//static int	check_exist_heredoc(void)
//{
//	if (access(HEREDOC_NAME, F_OK) == 0)
//	{
//		if (unlink(HEREDOC_NAME) == -1)
//			return (error_system("unlink failed\n", errno), CMD_ERROR);
//	}
//	return (CMD_OK);
//}

//int	execute_heredoc(t_data *data, int index)
//{
//	int		i;
//	int		fd;

//	i = 0;
//	fd = -1;
//	while (data->cmd[index].nb_heredocs > i)
//	{
//		if (fd != -1)
//			close(fd);
//		if (check_exist_heredoc() != CMD_OK)
//			return (CMD_ERROR);
//		fd = creat_here_doc(data->cmd[index].limiters[i]);
//		if (fd == -1)
//			return (error_system("create heredoc failed\n", errno), CMD_ERROR);
//		i++;
//	}
//	if (data->cmd[index].here_doc_in == true)
//	{
//		if (dup_files(fd, STDIN_FILENO) != CMD_OK)
//			return (CMD_ERROR);
//	}
//	close(fd);
//	unlink(HEREDOC_NAME);
//	return (CMD_OK);
//}

//// Modify heredoc system for multiple heredoc in multiple command
