/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 00:21:25 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/24 00:01:40 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	close_free_fd(t_cmd *cmd, int index)
{
	if (cmd[index].infiles != NULL)
		free_2d_array(cmd[index].infiles);
	if (cmd[index].outfiles != NULL)
		free_2d_array(cmd[index].outfiles);
	if (cmd[index].fd_infile > 2)
		close(cmd[index].fd_infile);
	if (cmd[index].fd_outfile > 2)
		close(cmd[index].fd_outfile);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_cmd_struct(t_cmd *cmd, int nb_cmd)
{
	int	i;

	i = 0;
	while (i < nb_cmd)
	{
		if (cmd[i].cmd != NULL)
			free_2d_array(cmd[i].cmd);
		if (cmd[i].files != NULL)
			free_2d_array(cmd[i].files);
		if (cmd[i].type != NULL)
			free(cmd[i].type);
		if (cmd[i].error_str != NULL)
			free(cmd[i].error_str);
		if (cmd[i].path != NULL)
			free(cmd[i].path);
		if (cmd[i].limiters != NULL)
			free_2d_array(cmd[i].limiters);
		close_free_fd(cmd, i);
		i++;
	}
	if (cmd)
		free(cmd);
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
}

void	free_data_struct(t_data *data)
{
	if (data->cmd)
		free_cmd_struct(data->cmd, data->pipe_len);
}
