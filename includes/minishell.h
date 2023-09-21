/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:37:45 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/20 18:51:26 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"
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
	// bool			op;
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
	e_filename,
	e_argument,
}	t_tk_type;

typedef	struct s_tokens
{
	char **tokens;
	t_tk_type *token_type;
	int	pipe_count;
	int	token_count;
	int cmd_count;
}	t_tokens;


int	lenoptr(char *line);
int	lenquote(char *line);
int split_token(char *line, t_tokens *stuff);


#endif