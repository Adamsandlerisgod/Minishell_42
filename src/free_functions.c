/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:21:25 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/01 12:11:32 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_cmd_struct(t_cmd *cmd)
{
	int i;

	i = 0;
	if (cmd->cmd != NULL)
		free_2d_array(cmd->cmd);
	if (cmd->limiters != NULL)
	free_2d_array(cmd->limiters);
	if (cmd->infiles != NULL)
	free_2d_array(cmd->infiles);
	if (cmd->outfiles != NULL)
		free_2d_array(cmd->outfiles);
	if (cmd)
		free(cmd);
	// free(cmd);
}

void	free_tokens(t_tokens *tokens)
{
	if (tokens->tokens != NULL)
		free_2d_array (tokens->tokens);
	if (tokens->token_type != NULL)
		free(tokens->token_type);
	tokens->pipe_count = 0;
	tokens->token_count = 0;
	tokens->cmd_count = 0;
	if (tokens->arg_count != NULL)
		free(tokens->arg_count);
	if (tokens->heredoc_count != NULL)
		free(tokens->heredoc_count);
	if (tokens->infile_count != NULL)
		free(tokens->infile_count);
	if (tokens->outfile_count != NULL)
		free(tokens->outfile_count);
	if (tokens->append_count != NULL)
		free(tokens->append_count);
	// if (tokens != NULL)
	// 	free(tokens);
}

void	free_data_struct(t_data *data)
{
	free_cmd_struct(data->cmd);
	// free_env(data->env);
	free(data);
}