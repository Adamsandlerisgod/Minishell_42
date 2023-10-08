/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 14:01:49 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/09 02:06:20 by jhurpy           ###   ########.fr       */
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
#include <errno.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define HEREDOC_NAME "/tmp/.here_doc"
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
	int		pipe_len;
	int		pipefd[2];
}		t_data;

typedef struct s_env
{
	char	*name;
	t_env	*next;
}		t_env;

typedef struct s_cmd
{
	char			**cmd;
	bool			pipe_in;
	bool			pipe_out;
	bool			here_doc_in;
	int				nb_heredocs;
	char			**limiters;
	bool			file_in;
	char			**infiles;
	bool			file_out;
	char			**outfiles;
	bool			*append;
}			t_cmd;

/*Creation of the envirronement of minishell*/

t_env	*set_env(char **env);
void	free_env(t_env *my_env);
char	**env_array(t_env *env);

/*Executation part: execute a list of pipe command in childs or parent*/

int		separator_op(t_data *data);
pid_t	fork_process(t_data *data, char **env, int index);
void	execute_cmd(char *av, char **env);
int		prepare_builtins_exec(t_data *data, char **env, int index);
int		execute_builtins(t_data *data, char **env, int index);
bool	is_builtins(t_data *data, int index);

/*Redirection part: open files, pipe and dup the input and ouput*/

int		redirection(t_data *data, int index);
int		dup_files(int fd_origin, int fd_target);
int		open_files(t_data *data, int index);
int		creat_here_doc(char *limiter);

/*Builtins part: list of the builtins command*/

int		ft_echo(t_data *data, int index);
int		ft_cd(t_data *data, int index);
int		ft_pwd(t_data *data, int index);
int		ft_export(t_data *data, char **env, int index);
int		ft_unset(t_data *data, int index);
int		ft_env(t_data *data, char **env, int index);
int		ft_exit(t_data *data, int index);

/*Utils*/

int		len_variable(char *var);
bool	check_var(char *var);
void	print_env(char **env);

/*Message part: return  the error message system or command*/

void	error_system(char *msg, int errno);
void	error_cmd(char *cmd, char *msg);

#endif
