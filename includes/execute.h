/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:01:49 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 15:29:48 by jhurpy           ###   ########.fr       */
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

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define CMD_OK 0
# define CMD_ERROR 1
# define CMD_EXIT 2
# define CMD_NOT_EXEC 126
# define CMD_NOT_FOUND 127


typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;
	int		status;
}		t_data;

typedef struct s_env
{
	char	*name;
	t_env	*next;
}		t_env;

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

/*Error message management*/
void	msg_cmd(char *cmd, char *msg);

/*Creation of the envirronement of minishell*/

t_env	*set_env(char **env);
void	free_env(t_env *my_env);

/*Executation part: execute a list of pipe command in childs or parent*/

int		separator_op(t_data *data, char **ev, int len);
pid_t	*fork_process(size_t len, t_data *data, char **ev, int index);
void	child_process(int pipefd[2], t_cmd *cmd, char **ev, int index);
void	parent_process(t_data *data, int pipefd[2]);
void	execute_cmd(char *av, char **ev);

/*Builtins part: list of the builtins command*/

int		ft_echo(t_cmd *cmd, int index);
int		ft_cd(t_cmd *cmd, t_env *env, int index);
int		ft_pwd(t_cmd *cmd, int index);
int		ft_export(t_data *data, int index);
int		ft_unset(t_data *data, int index);
int		ft_exit(t_data *data, int index);

#endif
