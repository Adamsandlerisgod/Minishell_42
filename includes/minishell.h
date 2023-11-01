/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:37:45 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/01 19:11:30 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
#include <stdbool.h>
#include <string.h>
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

// typedef	struct s_token
// {
// 	char 			*str;
// 	int				type;
// 	struct s_token	*next;
// 	struct s_token	*prev;

// }				t_token;

typedef struct s_env
{
	char	*name;
	struct s_env	*next;
}		t_env;

typedef struct s_cmd
{
	char			**cmd;
	bool			pipe_in;
	bool			pipe_out;
	bool			here_doc_in;
	int				here_doc_fd;
	int				nb_heredocs;
	char			**limiters;
	bool			file_in;
	char			**infiles;
	bool			file_out;
	char			**outfiles;
	bool			append;
}			t_cmd;

typedef struct s_data
{
	t_cmd	*cmd;
	t_env	*env;
	int		status;
	int		pipe_len;
	int		pipefd[2];
}		t_data;

typedef enum e_type_token
{
	e_void,
	e_rdrt,
	e_pipe,
	e_name,
	e_argument,
}	t_tk_type;

typedef	struct s_tokens
{
	char **tokens;
	t_tk_type *token_type;
	int	pipe_count;
	int	token_count;
	int cmd_count;
	int *arg_count;
	int *heredoc_count;
	int *infile_count;
	int *outfile_count;
	int *append_count;
}	t_tokens;

/*Environment*/
t_env	*set_env(char **env);
void	free_env(t_env *my_env);
char	**env_array(t_env *env);

/*checker*/
int		lenoptr(char *line);
int		lenquote(char *line);
int		lenvar(char *line);
bool	ft_istoken(int c);
bool	ft_isoptr(int c);
bool	checker(char *line);

/*split_token*/
int 	split_token(char *line, t_tokens *stuff);

/*token_identify & syntax*/
bool	token_identify(t_tokens *tokens);
bool 	token_syntax(t_tokens *tokens);

/*Expand_var*/
bool	expandinator(t_tokens *tokens, t_env *env);
bool	expand_var(t_env *env, char **token, char *pos, char **next_pos);

/*Quote_trim*/
bool quote_trim(t_tokens *tokens);

/*Struct_fill*/
bool	struct_fill(t_tokens *tokens, t_data *data);

/*Executation*/

bool	builtin_in_parent(t_data *data, char **env, int index);
int		execute_builtins(t_data *data, char **env, int index);
bool	is_builtins(t_data *data, int index);
void	execute_cmd(char **cmd, char **env);
pid_t	fork_process(t_data *data, char **env, int index);
int		separator_op(t_data *data);

/*Redirection*/

int		dup_files(int fd_target, int fd_origin);
int		execute_heredoc(t_data *data, int index);
int		redir_infiles(t_data *data, int index);
int		redir_outfiles(t_data *data, int index);
int		redirection_pipes(t_data *data, int index);
int		redirection_files(t_data *data, int index);
int		check_access_files(t_data *data, int index);

/*Builtins*/

int		ft_echo(t_data *data, int index);
int		ft_cd(t_data *data, int index);
int		ft_pwd(t_data *data, int index);
int		ft_export(t_data *data, char **env, int index);
int		ft_unset(t_data *data, int index);
int		ft_env(t_data *data, char **env, int index);
int		ft_exit(t_data *data, int index);
int		len_variable(char *var);
bool	check_var(char *var);
void	print_env(char **env);

/*Messages*/

void	error_system(char *msg, int errno);
void	error_cmd(char *cmd, char *msg);

#endif