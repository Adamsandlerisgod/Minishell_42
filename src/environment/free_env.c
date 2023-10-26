/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:22 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 18:36:37 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

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
