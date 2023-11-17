/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:22 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/15 21:10:49 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function free_env() is used to free the environment variable.
*/

void	free_env(t_env *my_env)
{
	t_env	*tmp;

	while (my_env)
	{
		tmp = my_env;
		my_env = my_env->next;
		free(tmp->name);
		free(tmp);
	}
}
