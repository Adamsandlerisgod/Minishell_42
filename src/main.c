/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 13:39:09 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/01 17:00:21 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void init_mini(t_mini *stuff)
{

}



bool	proccessor(char *line, t_mini *stuff, char **env)
{
	add_history(line);
	if (!(syntax_check(line, stuff)))
		return (false);
}

int main(int ac, char **argv, char **env)
{
	t_mini		stuff;
	char		*line;

	void(*argv);
	if (ac > 1)
		return(printf("No arguments please"));
	init_mini(&stuff); /*This should initialize struct, and get the environment into its char array*/
	while (true)
	{
		line = readline("msh : ");
		if (*line && !(processer(line, env, &stuff)))
			free_mini(&stuff);
		free(line);
	}
	
}