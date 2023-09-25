/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:29 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 15:26:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

static void	init_varaible(t_env *tmp, char *env)
{
	int		i;
	char	*tmp_i;

	i = 0;
	if (ft_strncmp(*env, "SHLVL=", 6) == 0)
	{
		i = ft_atoi(*env + 6);
		tmp_i = ft_itoa(i + 1);
		tmp->name = ft_strjoin("SHLVL=", tmp_i);
		free(tmp_i);
	}
	else
		tmp->name = ft_strdup(env);
}

static void	creat_new_env(t_env *my_env, char **env)
{
	t_env	*tmp;

	tmp = my_env;
	while (*env)
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			// Error message management; malloc failed (EXIT FAILURE)
		init_varaible(tmp, env);
		tmp->next = NULL;
		tmp = tmp->next;
		env++;
		if (ft_strncmp(*env, "OLDPWD=", 7) == 0)
			env++;
	}
}

/*
The function set_env is used to set the environment variable when starting
the minishell.
*/

t_env	*set_env(char **env)
{
	t_env	*my_env;

	if (!env)
		// Error message management; env is NULL (EXIT FAILURE)
	creat_new_env(my_env, env);
	return (my_env);
}
