/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 21:04:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 21:04:48 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	creat_here_doc(char *limiter)
{
	char	*line;
	int		fd;

	fd = open(HEREDOC_NAME, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
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
