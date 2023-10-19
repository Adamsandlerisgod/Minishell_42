#include <stdio.h>
#include <stdbool.h>
#include "your_header.h" // Include your header file that contains struct definitions and function prototypes
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:46:32 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/16 16:38:27 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// {
// 	t_cmd	*cmd;
// 	t_env	*env;
// 	int		status;
// 	int		pipe_len;
// 	int		pipefd[2];
// }		t_data;

// typedef struct s_cmd
// {
// 	char			**cmd;
// 	bool			pipe_in;
// 	bool			pipe_out;
// 	bool			here_doc_in;
// 	int				nb_heredocs;
// 	char			**limiters;
// 	bool			file_in;
// 	char			**infiles;
// 	bool			file_out;
// 	char			**outfiles;
// 	bool			*append;
// }			t_cmd;

// typedef	struct s_tokens
// {
// 	char **tokens;
// 	t_tk_type *token_type;
// 	int	pipe_count;
// 	int	token_count;
// 	int cmd_count;
// }	t_tokens;
#include "../../includes/minishell.h"

void	init_cmd(t_cmd *cmd, int j, t_tokens *tokens)
{
	if (j < (tokens->pipe_count + 1))
		cmd->pipe_in = TRUE;
	else
		cmd->pipe_in = FALSE;
	if (j > 0)
		cmd->pipe_out = TRUE;
	else
		cmd->pipe_out = FALSE;
	cmd->here_doc_in = FALSE;
	cmd->file_in = FALSE;
	cmd->file_out = FALSE;
	cmd->append = FALSE;
	cmd->here_doc = NULL;
}

void	mallocer(t_cmd *cmd, t_tokens *tokens, int j)
{
	if (tokens->cmd_count)
		cmd->cmd = (char **)calloc(sizeof(char *), (tokens->cmd_count + 1));
	if (tokens->heredoc_count[j])
	{
		cmd->limiters = (char **)calloc(sizeof(char *), (tokens->heredoc_count[j] + 1));
		cmd->nb_heredocs = tokens->heredoc_count;
	}	
	if (tokens->infile_count[j])
		cmd->infiles = (char **)calloc(sizeof(char *), (tokens->infile_count[j] + 1));
	if (tokens->outfile_count[j] || tokens->append_count[j])
	{
		cmd->outfiles = (char **)calloc(sizeof(char *), 
			(tokens->outfile_count[j] + tokens->append_count[j] + 1));
	}
}

void	sort_rdrt(t_cmd *cmd, char *token, char *next_token)
{
	int i;

	i = 0;
	if(ft_strncmp("<<", token, 2) == 0)
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

t_cmd	identify_2(t_cmd *cmd, t_tokens *tokens, int j, int *i)
{

	init_cmd(cmd, j, tokens);
	mallocer(cmd, tokens, j);
	while (tokens->token_type[*i] != e_pipe)
	{
		if (tokens->token_type[*i] == e_rdrt)
		{	
			sort_rdrt(&cmd, tokens->tokens[*i], tokens->tokens[*i + 1]); 
			*i += 2;
			/*Only works bc token_syntax makes sure no pipe or rdrt comes after*/
		}
		else if (tokens->token_type[*i] == e_argument)
		{
			cmd->cmd = ft_strdup(tokens->tokens[*i]);
			*i += 1;
		}
	}
}

bool	struct_fill(t_tokens *tokens, t_data *data)
{
	int i;
	int j;
	t_cmd	*cmd_struct;

	cmd_struct = (t_cmd *)malloc(sizeof(t_cmd) * (tokens->pipe_count + 2);
	i = 0;
	j = 0;
	while (j < tokens->pipe_count + 1)
	{
		cmd_struct[j] = identify_2(&cmd_struct[j], &tokens, j, &i);
		j++;
	}
	cmd_struct[j] = NULL;
}

int main() {
    // Create a t_tokens structure and initialize it with some sample data
    t_tokens tokens;
    tokens.tokens = (char *[]){"ls", ">", "output.txt", NULL}; // Replace with your token data
    tokens.token_type = NULL; // Replace with your token type data
    tokens.pipe_count = 0; // Replace with the number of pipes
    tokens.token_count = 3; // Replace with the total number of tokens
    tokens.cmd_count = 1; // Replace with the total number of commands

    // Create a t_data structure to hold the result
    t_data data;

    // Call the struct_fill function with the t_tokens and t_data structures
    bool success = struct_fill(&tokens, &data);

    // Check if the function executed successfully
    if (success) {
        // Print the results or perform other tests
        printf("Function executed successfully.\n");

        // Access data in the data structure and print it
        if (data.cmd) {
            printf("Command: %s\n", data.cmd[0]);
        }

        if (data.env) {
            // Print env data if needed
        }

        if (data.status) {
            // Print status data if needed
        }

        // Clean up allocated memory if needed
    } else {
        // Handle the case when the function didn't execute successfully
        printf("Function failed.\n");
    }

    return 0;
}
