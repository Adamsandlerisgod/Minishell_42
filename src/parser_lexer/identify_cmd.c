/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:25:44 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/24 13:45:15 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	malloc_cmd(t_cmd *cmd, t_tokens *tokens, int j)
{
	cmd->cmd = (char **)ft_calloc(sizeof(char *),
			((tokens->arg_count[j]) + 1));
	cmd->limiters = (char **)ft_calloc(sizeof(char *),
			(tokens->heredoc_count[j] + 1));
	cmd->nb_heredocs = tokens->heredoc_count[j];
	cmd->infiles = (char **)ft_calloc(sizeof(char *),
			(tokens->infile_count[j] + 1));
	cmd->outfiles = (char **)ft_calloc(sizeof(char *),
			(tokens->outfile_count[j] + tokens->append_count[j] + 1));
	cmd->files = (char **)ft_calloc(sizeof(char *),
			(tokens->outfile_count[j] + tokens->append_count[j]
				+ tokens->infile_count[j] + tokens->heredoc_count[j] + 1));
	cmd->type = (t_rdrt_type *)ft_calloc(sizeof(t_rdrt_type),
			(tokens->outfile_count[j] + tokens->append_count[j]
				+ tokens->infile_count[j] + tokens->heredoc_count[j] + 1));
}

static void	sort_rdrt_type(t_cmd *cmd, char *token, char *next_token)
{
	int	i;

	i = 0;
	while ((cmd->files[i]))
		i++;
	cmd->files[i] = ft_strdup(next_token);
	if (ft_strncmp("<<", token, 2) == 0)
		cmd->type[i] = e_heredoc;
	else if (*token == '<')
		cmd->type[i] = e_infile;
	else if (ft_strncmp(">>", token, 2) == 0)
		cmd->type[i] = e_append;
	else
		cmd->type[i] = e_outfile;
}

static void	store_rdrt(t_cmd *cmd, char *token, char *next_token)
{
	int	i;

	i = 0;
	sort_rdrt_type(cmd, token, next_token);
	if (ft_strncmp("<<", token, 2) == 0)
	{
		while ((cmd->limiters[i]))
			i++;
		cmd->limiters[i] = ft_strdup(next_token);
	}
	else if (*token == '<')
	{
		while ((cmd->infiles[i]))
			i++;
		cmd->infiles[i] = ft_strdup(next_token);
	}
	else
	{
		while ((cmd->outfiles[i]))
			i++;
		cmd->outfiles[i] = ft_strdup(next_token);
	}
}

static void	find_last_rdrt(t_cmd *cmd, t_tokens *tokens, int i)
{
	while (tokens->token_type[i] != e_pipe && i != 0)
	{
		if (!(ft_strncmp(tokens->tokens[i], "<<", 2)))
		{
			cmd->here_doc_in = TRUE;
			break ;
		}
		else if (!(ft_strncmp(tokens->tokens[i], "<", 1)))
		{
			cmd->file_in = TRUE;
			break ;
		}
		i--;
	}
}

void	identify_cmd(t_cmd *cmd, t_tokens *tokens, int j, int *i)
{
	int	x;

	x = 0;
	assign_cmd(cmd, j, tokens);
	malloc_cmd(cmd, tokens, j);
	while (*i < tokens->token_count && tokens->token_type[*i] != e_pipe)
	{
		if (tokens->token_type[*i] == e_rdrt)
		{
			store_rdrt(cmd, tokens->tokens[*i], tokens->tokens[*i + 1]);
			*i += 2;
		}
		else if (tokens->token_type[*i] == e_argument)
		{
			cmd->cmd[x] = ft_strdup(tokens->tokens[*i]);
			*i += 1;
			x++;
		}
	}
	find_last_rdrt(cmd, tokens, *i - 1);
}
