/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:01:49 by jhurpy            #+#    #+#             */
/*   Updated: 2023/08/30 10:38:36 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>

typedef struct s_cmd
{
	char			**cmd;
	bool			pipe;
	char			*infile;
	char			*outfile;
	bool			here_doc;
	char			*limiter;
	bool			append;
	bool			op;
}			t_cmd;

int		separator_op(t_cmd *cmd, char **ev, int len);
pid_t	*fork_process(size_t len, t_cmd *cmd, char **ev, int index);
void	child_process(int pipefd[2], t_cmd *cmd, char **ev, int index);
void	execute_cmd(char *av, char **ev);

#endif
