/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:37:45 by whendrik          #+#    #+#             */
/*   Updated: 2023/12/12 18:51:41 by whendrik         ###   ########.fr       */
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
#include <errno.h>
#include <termios.h>


# define RESET "\033[0m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RED "\033[1;32m"
# define GREEN "\033[1;32m"

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# define true 1
# define false 0

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define CMD_OK 0
# define CMD_ERROR 1
# define CMD_EXIT 2
# define CMD_NOT_EXEC 126
# define CMD_NOT_FOUND 127


// typedef	struct s_token
// {
// 	char 			*str;
// 	int				type;
// 	struct s_token	*next;
// 	struct s_token	*prev;

// }				t_token;

extern int	g_status;

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
	size_t	pipe_len;
	int		pipefd[2];
	struct termios	term;
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
	int	status;
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
// t_env	*set_env(char **env);
// void	free_env(t_env *my_env);
char	**env_array(t_env *env);
void	add_variable(t_env *tmp_env, char *var);
char 	*get_env_value(char *var, t_env **env, int var_len, int status);


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
bool	expandinator(t_tokens *tokens, t_data *data);
bool	expand_var(t_data *data, char **token, char *pos, char **next_pos);

/*Quote_trim*/
bool quote_trim(t_tokens *tokens);

/*Struct_fill*/
bool	struct_fill(t_tokens *tokens, t_data *data);

/*Executation*/

bool	builtin_in_parent(t_data *data, char **env, int index);
int		execute_builtins(t_data *data, char **env, int index);
bool	is_builtins(t_data *data, int index);
void	execute_cmd(char **cmd, char **env);
pid_t	*fork_process(t_data *data, char **env, int index);
int		separator_op(t_data *data);

/*Redirection*/

int		dup_files(int fd_target, int fd_origin);
int		redirection_heredoc(t_data *data, int index);
int		redir_infiles(t_data *data, int index);
int		redir_outfiles(t_data *data, int index);
int		redirection_pipes(t_data *data, int index);
int		redirection_files(t_data *data, int index);
int		check_access_files(t_data *data, int index);
void	open_heredoc(t_data *data);

/*Builtins*/

int		ft_echo(t_data *data, int index);
int		ft_cd(t_data *data, int index);
int		ft_pwd(t_data *data, int index);
int		ft_export(t_data *data, char **env, int index);
int		ft_unset(t_data *data, int index);
int		ft_env(t_data *data, char **env, int index);
int		ft_exit(t_data *data, int index);
int		len_variable(char *var);
bool	check_variable(char *var);
void	print_env(char **env);

/*Messages*/

void	error_system(char *msg);
void	error_cmd(char *cmd, char *msg);

/*free_functions*/
void	free_2d_array(char **array);
void	free_cmd_struct(t_cmd *cmd);
void	free_tokens(t_tokens *tokens);
void	free_data_struct(t_data *data);

/*Signal functions*/
void	sigint_handler(int signum);
void	sigint_wait_handler(int signum);
bool	set_signal(void);
bool	set_termios(struct termios *term);
bool	restore_termios(struct termios *term);

#endif