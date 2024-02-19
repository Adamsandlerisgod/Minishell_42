/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:11 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 01:37:50 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_unset is used to remove environment variables.
The command do not take any option.
*/

static int	check_input_unset(t_data *data, int index)
{
	if (data->cmd[index].cmd[1] == NULL)
		return (CMD_OK);
	if (data->cmd[index].cmd[1][0] == '-')
	{
		error_cmd_msg("unset", data->cmd[index].cmd[1], NO_OPTION);
		return (CMD_ERROR);
	}
	return (CMD_OK);
}

static void	parce_list_var(t_env *env, char *var)
{
	t_env	*tmp_env;
	t_env	*prev_env;

	tmp_env = env;
	prev_env = NULL;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, var, ft_strlen(var)) == 0
			&& ft_strncmp(tmp_env->name + ft_strlen(var), "=", 1) == 0)
		{
			if (prev_env)
				prev_env->next = tmp_env->next;
			else
				env = tmp_env->next;
			free(tmp_env->name);
			free(tmp_env);
			break ;
		}
		prev_env = tmp_env;
		tmp_env = tmp_env->next;
	}
}

static void	remove_variable(t_env *env, char **var)
{
	char	*var_tmp;
	int		i;

	i = 1;
	while (var[i])
	{
		var_tmp = ft_substr(var[i], 0, ft_strlen(var[i]));
		parce_list_var(env, var_tmp);
		free (var_tmp);
		i++;
	}
}

static bool	is_wrong_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

void	ft_unset(t_data *data, int index)
{
	int	i;

	g_exit_status = check_input_unset(data, index);
	i = 1;
	while (data->cmd[index].cmd[i])
	{
		if (is_wrong_arg(data->cmd[index].cmd[i]) == true)
		{
			error_cmd_var("unset", NO_VALID_ID, data->cmd[index].cmd[i]);
			g_exit_status = CMD_ERROR;
		}
		i++;
	}
	remove_variable(data->env, data->cmd[index].cmd);
}
