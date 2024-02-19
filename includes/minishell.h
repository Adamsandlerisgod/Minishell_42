/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:37:45 by whendrik          #+#    #+#             */
/*   Updated: 2024/01/24 14:33:22 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdbool.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <termios.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/* ************************************************************************** */
/*                                                                            */
/*                               MACRO PROMPT                                 */
/*                                                                            */
/* ************************************************************************** */

# define PROMPT			"minishell-hh$ "
# define PROMPT_R		"minishell-hh: "

/* ************************************************************************** */
/*                                                                            */
/*                           MACRO ERROR SYSTEM                               */
/*                                                                            */
/* ************************************************************************** */

# define MALLOC_ERROR	"malloc failed"
# define PIPE_ERROR		"pipe failed"
# define FORK_ERROR		"fork failed"
# define DUP_ERROR		"dup2 failed"

/* ************************************************************************** */
/*                                                                            */
/*                           MACRO ERROR COMMAND                              */
/*                                                                            */
/* ************************************************************************** */

# define CMD_OK 		0
# define LAST_CMD		-1
# define CMD_ERROR		1
# define NO_CMD			"command not found"
# define F_DENIED		"Permission denied"
# define NO_VAR			"not set"
# define CMD_NOT_EXEC	126
# define IS_DIR			"is a directory"
# define CMD_NOT_FOUND	127
# define NO_FILE		"No such file or directory"

/* ************************************************************************** */
/*                                                                            */
/*                           MACRO ERROR BUILTINS                             */
/*                                                                            */
/* ************************************************************************** */

# define NO_OPTION		"no option accepted"
# define NO_OPT_ARG		"no option or argument accepted"
# define TOO_MANY_ARG	"too many arguments"
# define NUM_ARG		"numeric argument required"

/* ************************************************************************** */
/*                                                                            */
/*                           MACRO ERROR SYNTAX                               */
/*                                                                            */
/* ************************************************************************** */

# define SYNTAX_ERROR	"syntax error near unexpected token "
# define NO_VALID_ID	"not a valid identifier"

/* ************************************************************************** */
/*                                                                            */
/*                               MACRO SIGNAL                                 */
/*                                                                            */
/* ************************************************************************** */

# define HANDLE_SIGINT_PARENT 1
# define IGNORE_SIGINT_PARENT 2
# define IGNORE_SIGQUIT 3

/* ************************************************************************** */
/*                                                                            */
/*                              GLOBAL VARIABLE                               */
/*                                                                            */
/* ************************************************************************** */

int	g_exit_status;

typedef struct s_env
{
	char			*name;
	struct s_env	*next;
}		t_env;

typedef enum e_type_rdrt
{
	e_infile,
	e_heredoc,
	e_outfile,
	e_append,
}	t_rdrt_type;

typedef struct s_cmd
{
	char			**cmd;
	char			**files;
	t_rdrt_type		*type;
	int				status;
	char			*error_str;
	char			*msg_error;
	char			*path;
	int				fd_infile;
	int				fd_outfile;
	bool			pipe_in;
	bool			pipe_out;
	bool			here_doc_in;
	int				here_doc_fd;
	int				nb_heredocs;
	char			**limiters;
	bool			file_in;
	bool			file_out;
	char			**infiles;
	char			**outfiles;
	bool			append;
}			t_cmd;

typedef struct s_data
{
	t_cmd				*cmd;
	t_env				*env;
	char				**ev_array;
	size_t				pipe_len;
	int					pipefd[2];
	struct sigaction	sa_i;
	struct sigaction	sa_q;
}		t_data;

typedef enum e_type_token
{
	e_void,
	e_rdrt,
	e_pipe,
	e_name,
	e_argument,
}	t_tk_type;

typedef struct s_tokens
{
	char		**tokens;
	t_tk_type	*token_type;
	int			pipe_count;
	int			token_count;
	int			cmd_count;
	int			*arg_count;
	int			*heredoc_count;
	int			*infile_count;
	int			*outfile_count;
	int			*append_count;
}	t_tokens;

// Builtins
void	ft_echo(t_data *data, int index);
void	ft_cd(t_data *data, int index);
void	ft_pwd(t_data *data, int index);
void	ft_export(t_data *data, char **env, int index);
void	ft_unset(t_data *data, int index);
void	ft_env(t_data *data, char **env, int index);
void	ft_exit(t_data *data, int index);

// Parser Lexer
void	assign_path(t_data *data);
bool	check_line(char *line);
void	identify_cmd(t_cmd *cmd, t_tokens *tokens, int j, int *i);
void	assign_cmd(t_cmd *cmd, int j, t_tokens *tokens);
bool	quote_trim(t_tokens *tokens);
int		split_tokens(char *line, t_tokens *stuff);
bool	token_identify(t_tokens *tokens, int i);
bool	token_syntax(t_tokens *tokens);
bool	variable_parser(t_tokens *tokens, t_data *data);

// Environment
void	free_env(t_env *my_env);
char	*get_env_value(char *var, t_env **env, int var_len, int status);
char	**env_array(t_env *env);
t_env	*set_env(char **env);

// Execution
bool	is_builtins(t_data *data, int index);
void	child_process(t_data *data, char **env, int index);
void	execute_builtins(t_data *data, char **env, int index);
bool	builtin_in_parent(t_data *data, int index);
pid_t	*fork_process(t_data *data, char **env, int index);
void	separator_op(t_data *data);

// Message
void	error_cmd(char *cmd, char *msg);
void	error_cmd_var(char *cmd, char *msg, char *str);
void	error_cmd_msg(char *cmd1, char *cmd2, char *msg);
void	error_system(char *msg);
void	error_exit_msg(char *arg, char *str, int flag);
void	error_input(char *msg, char *msg_type);
void	error_file_msg(char *file, char *msg);

// Redirection
void	assign_fd(t_data *data, int index);
bool	open_heredoc(t_data *data);

// Signal
void	open_quit_signal_on_valid_cmd(t_data *data, int index);
void	sigint_parent_handler(int signum);
void	sigint_child_handler(int signum);
void	set_signal(t_data *data, int type);
void	init_signal(t_data *data);
void	set_echo_ctl(int enable);
void	exit_status(int status);
void	exit_ctrl_d(t_data *data);

// Utils
void	free_2d_array(char **array);
void	free_cmd_struct(t_cmd *cmd, int nb_cmd);
void	free_tokens(t_tokens *tokens);
void	free_data_struct(t_data *data);

void	init_data(t_data *data, char **ev);
void	init_tokens(t_tokens *tokens);
void	init_data_cmd(t_cmd *cmd);

char	*join_path_cmd(char **path_array, char *command);
int		len_variable(char *var);
bool	check_variable(char *var);
void	print_env(char **env, int flag);
void	add_variable(t_env *tmp_env, char *var);
bool	check_long_long(char *str);
char	*get_home_oldpwd_path(char *var, t_data *data);

bool	is_operator(int c);
int		len_var(char *line);
int		len_operator(char *line);
int		len_quote(char *line);

#endif