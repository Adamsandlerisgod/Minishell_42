/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:39:09 by whendrik          #+#    #+#             */
/*   Updated: 2023/12/07 15:42:23 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_test(char **tokens, int tc)
{
	int i = 0;
	while(i < tc && *tokens != NULL)
	{
			printf("tokens[%d] = %s \n", i, tokens[i]);
			i++;
	}
}
void print_test_struct(t_data *data, t_tokens *tokens)
{
	int i = 0;

	while (i < tokens->pipe_count + 1)
	{
		printf("cmd_struct[%d] \n", i);
		print_test(data->cmd[i].cmd, tokens->arg_count[i]);
		print_test(data->cmd[i].limiters, tokens->heredoc_count[i]);
		print_test(data->cmd[i].infiles, tokens->infile_count[i]);
		print_test(data->cmd[i].outfiles, tokens->outfile_count[i] + tokens->append_count[i]);
		printf("pipe_out = %d\n", data->cmd[i].pipe_out);
		printf("pipe_in = %d\n", data->cmd[i].pipe_in);
		printf("heredoc in = %d\n", data->cmd[i].here_doc_in);
		printf("heredoc fd = %d\n", data->cmd[i].here_doc_fd);
		printf("heredoc nb = %d\n", data->cmd[i].nb_heredocs);
		printf("file_in = %d\n", data->cmd[i].file_in);
		printf("file_out = %d\n", data->cmd[i].file_out);
		printf("append = %d\n", data->cmd[i].append);
		i++;
	}
}

char **create_fake_environment() {
    char **env = (char **)malloc(sizeof(char *) * 5);

    // Create fake environment variables
    env[0] = ft_strdup("PATH=/bin:/usr/bin");
    env[1] = ft_strdup("HOME=/home/user");
    env[2] = ft_strdup("USER=testuser");
    env[3] = ft_strdup("INSHALLAH=bushdid911");
    env[4] = NULL;  // The last element should be NULL to indicate the end of the environment.

    return env;
}

void init_data(t_data *data, t_env *env)
{
	data->cmd = NULL;
	
	data->env = env;
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
	add_history(line);
	if (!(checker(line)))
		return (false);
	// printf("checker \n");
	if(!(split_token(line, tokens)))
		return (false);
	// printf("split_token\n");
	if (!(token_identify(tokens))) /*Needs adapting for s_cmd struct*/
		return (false);
	// printf("token_identify\n");
	if (!(token_syntax(tokens)))	/*Needs fixing(incomplete)*/
		return(false);
	if (!(expandinator(tokens, data->env)))
		return(false);
	// printf("Expandinator \n");
	// print_test(tokens->tokens, tokens->token_count);
	if (!(quote_trim(tokens)))
		return (false);
	// printf("Quote trimmer \n");
	// print_test(tokens->tokens, tokens->token_count);
	if (!(struct_fill(tokens, data)))
		return (false);
	data->pipe_len = tokens->pipe_count + 1;
	printf("Struct Filler\n");
	// print_test_struct(data, tokens);
	if ((separator_op(data) == CMD_ERROR))
		return (printf("ITS JEREMY'S FAULT"), false);
	// printf("ITS JEREMY'S FAULT correct \n");
	if (tokens != NULL)
		free_tokens(tokens);
	print_test_struct(data, tokens);
	if (data->cmd)
		free_cmd_struct(data->cmd);
	return (true);
}

int main(int ac, char** argv, char **ev)
{
	t_data		data;
	char		*line;
	t_tokens	tokens;
	t_env		*env;
	// char **fake_env = create_fake_environment(); 
	// int i = 0;
	
	(void)argv;
	if (ac != 1)
		exit(1);
	env = set_env(ev);
	// env	= create_fake_environment();
	// while(env[i])
	// 	printf("%s \n", env[i++]);
	// printf("before init_data\n");
	// print_env(argv);
	// print_env(env);
	init_data(&data, env); /*This should initialize struct, and get the environment into its char array*/
	init_tokens(&tokens);
	printf("after init_data\n");
	while (true)
	{
		// printf ("HERE MAIN \n");
		line = readline("minishell : ");
		// line = strdup(" \'$U\"S\"ER\' >> fe faggot > fa > fo < fum < fur << fuyo| car | wigger \'$USERBushabitch$HOME\'");
		// line = strdup("echo \"dog\"\'frog\'");
		if (*line && !(processor(line, &data, &tokens)))
		{
			printf("You have failed you sonofabitch\n");
			// break;
			// free_data_struct(&data);
		}
		// printf ("HERE MAIN 01 \n");
		free(line);
	}
	
	return (0);
}