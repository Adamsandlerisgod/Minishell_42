/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:39:09 by whendrik          #+#    #+#             */
/*   Updated: 2024/01/27 00:44:28 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static bool	assign_data_cmd(t_tokens *tokens, t_data *data)
{
	t_cmd	*cmd_struct;
	int		i;
	int		j;

	cmd_struct = (t_cmd *)malloc(sizeof(t_cmd) * (tokens->pipe_count + 1));
	if (cmd_struct == NULL)
		return (error_system(MALLOC_ERROR), false);
	i = 0;
	j = 0;
	while (j < tokens->pipe_count + 1)
	{
		init_data_cmd(&cmd_struct[j]);
		identify_cmd(&cmd_struct[j], tokens, j, &i);
		i += 1;
		j++;
	}
	data->cmd = cmd_struct;
	return (true);
}

static bool	processor_2(t_data *data, t_tokens *tokens)
{
	data->pipe_len = tokens->pipe_count + 1;
	if (open_heredoc(data) && g_exit_status == 1)
	{
		if (tokens != NULL)
			free_tokens(tokens);
		return (true);
	}
	assign_fd(data, 0);
	assign_path(data);
	if (tokens != NULL)
		free_tokens(tokens);
	separator_op(data);
	return (true);
}

static bool	processor(char *line, t_data *data, t_tokens *tokens)
{
	if (*line)
		add_history(line);
	if (!(check_line(line)))
		return (false);
	if (!(split_tokens(line, tokens)))
		return (false);
	if (!(token_identify(tokens, 0)))
		return (free_2d_array(tokens->tokens), false);
	if (!(token_syntax(tokens)))
		return (free_tokens(tokens), false);
	if (!(variable_parser(tokens, data)))
		return (false);
	if (!(quote_trim(tokens)))
		return (false);
	if (!(assign_data_cmd(tokens, data)))
		return (false);
	if (processor_2(data, tokens))
		return (true);
	return (false);
}

int	main(int ac, char **av, char **ev)
{
	t_data		data;
	t_tokens	tokens;
	char		*line;

	(void)av;
	g_exit_status = 0;
	if (ac != 1)
		exit(1);
	init_data(&data, ev);
	init_tokens(&tokens);
	while (1)
	{
		line = readline(PROMPT);
		if (!line)
			exit_ctrl_d(&data);
		if (line[0])
		{
			if (processor(line, &data, &tokens) && data.cmd)
				free_cmd_struct(data.cmd, data.pipe_len);
		}
		if (line)
			free(line);
	}
	return (g_exit_status);
}
