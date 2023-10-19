/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:37:45 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/19 14:35:39 by whendrik         ###   ########.fr       */
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
	int				here_doc_fd;
	int				nb_heredocs;
	char			**limiters;
	bool			file_in;
	char			**infiles;
	bool			file_out;
	char			**outfiles;
	bool			append;
}			t_cmd;

typedef enum e_type_rdrt
{
	e_input,
	e_output,
	e_heredoc,
	e_append,
}	t_type_rdrt;

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
bool 	token_syntax(t_tokens *tokens)

/*Expand_var*/
bool	expandinator(t_tokens *tokens, t_env *env);
bool	expand_var(t_env *env, char **token, char *pos, char **next_pos);

/*Quote_trim*/
bool quote_trim(t_tokens *tokens);

#endif