/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:00 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/07 17:43:12 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_variable(t_env *tmp_env, char *var)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		error_system("malloc failed\n", errno);
	new->name = ft_strdup(var);
	new->next = NULL;
	tmp_env->next = new;
}

static void	find_variable(t_env *env, char **var)
{
	t_env	*tmp_env;
	int		i;

	i = 0;
	while (var[i])
	{
		tmp_env = env;
		while (tmp_env)
		{
			if (ft_strncmp(tmp_env->name, var[i], len_variable(var[i])) == 0)
			{
				free(tmp_env->name);
				tmp_env->name = ft_strdup(var[i]);
			}
			else if (tmp_env->next == NULL)
				add_variable(tmp_env, var[i]);
			tmp_env = tmp_env->next;
		}
		i++;
	}
}

/*
The function export_builtins is used to add or change the value of
environment variables.
If export is called without arguments, it prints the environment.
If export is called with arguments, it adds or changes the value of
environment variables.
*/

int	ft_export(t_data *data, char **env, int index)
{
	int	status;
	int	i;

	status = CMD_OK;
	if (data->cmd[index].cmd[1] == NULL)
		return (print_env(env), status);
	if (data->cmd[index].cmd[1][0] == '-')
	{
		error_cmd(data->cmd[index].cmd[0], "no option accepted.");
		return (CMD_EXIT);
	}
	i = 1;
	while (data->cmd[index].cmd[i])
	{
		if (check_variable(data->cmd[index].cmd[i]) == false)
		{
			error_cmd(data->cmd[index].cmd[0], "invalid variable.");
			status = CMD_ERROR;
		}
		i++;
	}
	find_variable(data->env, data->cmd[index].cmd + 1);
	return (status);
}
