/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:39:09 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/11 20:10:33 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_mini(t_mini *stuff)
{

}


bool	proccessor(char *line, t_mini *stuff, char **env, t_tokens *tokens)
{
	add_history(line);
	if (!(checker(line)))
		return (false);
	if(!(split_token(line, &tokens)))
		return (false);
	if (!(token_identify(&tokens)))
		return (false);
	if (!(token_syntax(&tokens)))
		return(false);
	// quote_count(&tokens);
	if (!(expand_var(&tokens)))
		return(false);	
	if (!(quote_trim(&tokens)))
		return (false);
	
}

int main(int ac, char **argv, char **env)
{
	t_mini		stuff;
	char		*line;
	t_tokens	tokens;

	void(*argv);

	if (ac > 1)
		return(printf("Fuck outta here with your arguments please"));
	init_mini(&stuff); /*This should initialize struct, and get the environment into its char array*/
	while (true)
	{
		line = readline("minishell : ");
		if (*line && !(processer(line, env, &stuff, &tokens)))
			free_mini(&stuff);
		free(line);
	}
	
}