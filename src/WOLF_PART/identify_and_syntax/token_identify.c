/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:46:44 by whendrik          #+#    #+#             */
/*   Updated: 2023/12/01 12:08:12 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool type_count_malloc(t_tokens *tokens)
{
	int size;

	size = tokens->pipe_count + 1;
	tokens->arg_count = (int *)ft_calloc(sizeof(int) , (size + 1));
	if (tokens->arg_count == NULL)
		return (false);
	tokens->heredoc_count = (int *)ft_calloc(sizeof(int) , (size + 1));
	if (tokens->heredoc_count == NULL)
		return (false);
	tokens->infile_count = (int *)ft_calloc(sizeof(int) , (size + 1));
	if (tokens->infile_count == NULL)
		return (false);
	tokens->outfile_count = (int *)ft_calloc(sizeof(int), (size + 1));
	if (tokens->outfile_count == NULL)
		return (false);
	tokens->append_count = (int *)ft_calloc(sizeof(int) , (size + 1));	
	if (tokens->append_count == NULL)
		return (false);
	return (true);
}	

void	token_type_counter(t_tokens *tokens)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while(i < (tokens->pipe_count + 1) && j < tokens->token_count)
	{
		while (j < tokens->token_count && tokens->token_type[j] != e_pipe && tokens->token_type[j] != e_void)
		{
			if (!(ft_strncmp(tokens->tokens[j], "<<", 2)))
				tokens->heredoc_count[i] += 1;
			else if (!(ft_strncmp(tokens->tokens[j], ">>", 2)))
				tokens->append_count[i] += 1;
			else if (!(ft_strncmp(tokens->tokens[j], "<", 1)))
				tokens->infile_count[i] += 1;
			else if (!(ft_strncmp(tokens->tokens[j], ">", 1)))
				tokens->outfile_count[i] += 1;
			else if (tokens->token_type[j] == e_argument)
				tokens->arg_count[i] += 1;
			j++;
		}
		j++;
		i++;
	}
}

t_tk_type token_class(char *token, t_tk_type pre)
{
	if (!(ft_strncmp(token, "<>", 2)) || !(ft_strncmp(token, "><", 2)) 
		|| (lenoptr(token) > 2))
		return(e_void);
	if (*token == '<' || *token == '>')
		return (e_rdrt);
	else if (*token == '|')
		return (e_pipe);
	else if (pre == e_rdrt)
		return (e_name);
	else
		return (e_argument);
}

bool	token_identify(t_tokens *tokens)
{
	t_tk_type	*type;
	int			i;

	i = 0;
	type = NULL;
	type = (t_tk_type *)malloc(sizeof(t_tk_type) * (tokens->token_count + 1));
	if (!type)
		return (false);
	while (i < tokens->token_count)
	{
		if (i == 0)
			type[i] = token_class(tokens->tokens[i], e_void);
		else
			type[i] = token_class(tokens->tokens[i], type[i - 1]);
		if (type[i] == e_pipe)
			tokens->pipe_count += 1;
		if (type[i] == e_void)
		{
			free_tokens(tokens);/*error message*/
			return (false); /*syntax error near unexpected token `newline' */
		}
		i++;
	}
	tokens->token_type = type;
	if (!(type_count_malloc(tokens)))
		return (false, printf("type_count_malloc_failure")); /* Attend to when cleaning up*/
	token_type_counter(tokens);
	return (true);
}

/*Nice test*/
// void print_tokens(t_tokens *tokens) {
//     for (int i = 0; i < tokens->token_count; i++) {
//         printf("Token Type: %d\n", tokens->token_type[i]);
//         printf("Token: %s\n", tokens->tokens[i]);
//     }
// }