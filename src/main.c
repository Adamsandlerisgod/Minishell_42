/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:39:09 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/12 19:43:10 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_data(t_data *data, char **env)
{
	data->cmd = NULL;
	data->env = set_env(env);
	data->status = 1;	/*Uncertain can come back to this later*/
	data->pipe_len = 0;
	data->pipefd[2] = NULL; /*Uncertain as well*/
}


bool	proccessor(char *line, t_data *data, char **env, t_tokens *tokens)
{
	add_history(line);
	if (!(checker(line)))
		return (false);
	if(!(split_token(line, &tokens)))
		return (false);
	if (!(token_identify(&tokens))) /*Needs adapting for s_cmd struct*/
		return (false);
	if (!(token_syntax(&tokens)))	/*Needs fixing(incomplete)*/
		return(false);
	if (!(expand_var(&tokens)))
		return(false);	
	if (!(quote_trim(&tokens)))
		return (false);
	if (!(struct_fill(&tokens, &data)))
		return (false);
	
}

int main(int ac, char **env)
{
	t_data		data;
	char		*line;
	t_tokens	tokens;


	if (ac > 1)
		return(printf("Fuck outta here with your arguments please"));
	init_data(&data, env); /*This should initialize struct, and get the environment into its char array*/
	while (true)
	{
		line = readline("minishell : ");
		if (*line && !(processer(line, env, &data, &tokens)))
			free_data(&data);
		free(line);
	}
	
}