/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_parent_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 21:48:57 by jhurpy            #+#    #+#             */
/*   Updated: 2023/08/30 01:58:57 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/*
The function parent_process() executes the command in the parent process.
It takes as parameters:
	- pipefd: the pipe file descriptor
It returns nothing.
*/

void	parent_process(int pipefd[2])
{
	// insert condition for builtins cmds execute in parent process
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit_error("pipex: ", "dup2 failed ");
	close(pipefd[0]);
}
