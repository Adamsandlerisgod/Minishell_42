/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:01:49 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/11 06:52:31 by jhurpy           ###   ########.fr       */
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

typedef struct s_data
{
	t_cmd	*cmd;
}		t_data;

typedef struct s_cmd
{
	char			**cmd;
	bool			pipe;
	char			*infile;
	bool			in_redir;
	char			*outfile;
	bool			out_redir;
	bool			here_doc;
	char			*limiter;
	bool			append;
	bool			op;
}			t_cmd;

/*Creation of the envirronement of minishell*/

char	**set_env(char **env);

/*Executation part: execute a list of pipe command in childs or parent*/

int		separator_op(t_data *data, char **ev, int len);
pid_t	*fork_process(size_t len, t_data *data, char **ev, int index);
void	child_process(int pipefd[2], t_cmd *cmd, char **ev, int index);
void	parent_process(t_data *data, int pipefd[2]);
void	execute_cmd(char *av, char **ev);
void	exit_error(char *str1, char *str2);

/*Builtins part: list of the builtins command*/

int		echo_builtins(t_cmd *cmd, int i);
int		cd_builtins(t_cmd *cmd, char **ev, int i);
int		pwd_builtins(t_cmd *cmd, int i);
int		export_builtins();
int		unset_builtins();
int		env_builtins(t_cmd *cmd, char **env, int i);
int		exit_builtins();
void	msg_cmd(char *arg1, char *arg2, char *arg3, int fd);

#endif
