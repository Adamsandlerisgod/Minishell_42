/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:39:09 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/19 21:25:55 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_data(t_data *data, char **env)
{
	data->cmd = NULL;
	
	printf("before set_env\n");
	data->env = set_env(env);
	printf("post set_env\n");
	data->status = 1;	/*Uncertain can come back to this later*/
	data->pipe_len = 0;
	data->pipefd[1] = -1; /*Uncertain as well*/
}

void init_tokens(t_tokens *tokens)
{
	tokens->tokens = NULL;
	tokens->token_type = NULL;
	tokens->pipe_count = 0;
	tokens->token_count = 0;
	tokens->cmd_count = 0;
	tokens->arg_count = NULL;
	tokens->heredoc_count = NULL;
	tokens->infile_count = NULL;
	tokens->outfile_count = NULL;
	tokens->append_count = NULL;
}

bool	processor(char *line, t_data *data, t_tokens *tokens)
{
	// add_history(line);
	if (!(checker(line)))
		return (false);
	printf("checker\n");
	if(!(split_token(line, tokens)))
		return (false);
	printf("split_token\n");
	if (!(token_identify(tokens))) /*Needs adapting for s_cmd struct*/
		return (false);
	printf("token_identify\n");
	if (!(token_syntax(tokens)))	/*Needs fixing(incomplete)*/
		return(false);
	if (!(expandinator(tokens, data->env)))
		return(false);	
	if (!(quote_trim(tokens)))
		return (false);
	if (!(struct_fill(tokens, data)))
		return (false);
	return (true);
}

int main(int ac, char **env)
{
	t_data		data;
	char		*line;
	t_tokens	tokens;


	if (ac > 1)
		exit(1);
	printf("before init_data\n");
	init_data(&data, env); /*This should initialize struct, and get the environment into its char array*/
	init_tokens(&tokens);
	printf("after init_data\n");
	// while (true)
	// {
		// line = readline("minishell : ");
		line = strdup("Fuck | \"you| bi\" tch");
		if (*line && !(processor(line, &data, &tokens)))
			printf("YEET");
			// free_data(&data);
		free(line);
	// }
	
	return (0);
}