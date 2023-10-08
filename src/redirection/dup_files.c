/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:10:30 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/07 16:41:15 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	dup_files(int fd_target, int fd_origin)
{
	if (dup2(fd_target, fd_origin) == -1)
	{
		error_system("dup2 failed\n", errno);
		if (fd_origin != STDIN_FILENO && fd_origin != STDOUT_FILENO
			&& fd_origin != STDERR_FILENO)
			close(fd_origin);
		if (fd_target != STDIN_FILENO && fd_target != STDOUT_FILENO
			&& fd_target != STDERR_FILENO)
			close(fd_target);
		if (access(HEREDOC_NAME, F_OK) == 0)
			unlink(HEREDOC_NAME);
		return (CMD_ERROR);
	}
	return (CMD_OK);
}
