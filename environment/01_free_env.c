/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 14:27:48 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/15 14:41:45 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

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
