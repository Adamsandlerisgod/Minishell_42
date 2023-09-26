/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:38:45 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 01:16:18 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/*
The function init_my_env() initializes the environment variables.
It takes as parameters:
	- env: the environment variables
It returns nothing.
*/

static void	init_my_env(char **env)
{
	int		i;
	while (*env)
	{
		if (ft_strncmp(*env, "SHLVL=", 6) == 0)
		{
			i = ft_atoi(*env + 6);
			free(*env);
			*env = ft_strjoin("SHLVL=", ft_itoa(i + 1));
		}
		if (ft_strncmp(*env, "OLDPWD=", 7) == 0)
		{
			free(*env);
			*env = ft_strdup("OLDPWD");
		}
		env++;
	}
}

static int	count_line(char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
The function set_env() copies the environment variables in a new array.
It takes as parameters:
	- env: the environment variables
It returns the new array.
*/

char	**set_env(char **env)
{
	char	**my_env;

	my_env = (char **)malloc(sizeof(char *) * (count_line(env) + 1));
	if (!my_env)
		exit_error("minishell: ", "malloc failed ");
	my_env[count_line(env)] = NULL;
	while (*env)
	{
		*my_env = ft_strdup(*env);
		env++;
		my_env++;
	}
	init_my_env(my_env);
	return (my_env);
}
