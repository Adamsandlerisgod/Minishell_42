/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_jimmy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:29 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/16 17:18:53 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**env_array(t_env *env)
{
	t_env	*tmp;
	char	**ev;
	int		len_env;
	int		i;

	tmp = env;
	len_env = 0;
	i = 0;
	while (tmp)
	{
		len_env++;
		tmp = tmp->next;
	}
	tmp = env;
	ev = (char **)malloc(sizeof(char *) * (len_env + 1));
	if (ev == NULL)
	{
		error_system("malloc failed\n");
		return (NULL);
	}
	ev[len_env] = NULL;
	while (len_env--)
	{
		ev[len_env] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	return (ev);
}

static void	init_variable(t_env *tmp, char *env)
{
	int		i;
	char	*tmp_i;

	i = 0;
	if (ft_strncmp(env, "SHLVL=", 6) == 0)
	{
		i = ft_atoi(env + 6);
		tmp_i = ft_itoa(i + 1);
		tmp->name = ft_strjoin("SHLVL=", tmp_i);
		free(tmp_i);
	}
	else
		tmp->name = ft_strdup(env);
}

static t_env	*creat_new_env(char **env)
{
	t_env	*tmp;
	t_env	*tmp_return;
	int		i;

	tmp = NULL;
	tmp_return = tmp;
	i = 0;
	while (env[i])
	{
		tmp = (t_env *)malloc(sizeof(t_env));
		if (tmp == NULL)
			error_system("malloc failed\n");
		init_variable(tmp, env[i]);
		tmp->next = tmp_return;
		tmp_return = tmp;
		i++;
		if (env[i] != NULL)
		{
			if (ft_strncmp(env[i], "OLDPWD=", 7) == 0)
				i++;
		}
	}
	return (tmp);
}

/*
The function set_env is used to set the environment variable when starting
the minishell.
*/

t_env	*set_env(char **env)
{
	t_env	*my_env;

	my_env = NULL;
	if (!env)
	{
		ft_putstr_fd("Error: env is NULL\n", STDERR_FILENO);
		exit (CMD_ERROR);
	}
	my_env = creat_new_env(env);
	return (my_env);
}
