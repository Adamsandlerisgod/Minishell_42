/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:11 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/19 17:54:26 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parce_list_var(t_env *env, char *var)
{
	t_env	*tmp_env;
	t_env	*prev_env;

	tmp_env = env;
	prev_env = NULL;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, var, len_variable(var)) == 0)
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
	int		i;

	i = 0;
	while (var[i])
	{
		parce_list_var(env, var[i]);
		i++;
	}
}

/*
The function unset_builtins is used to remove environment variables.
*/

/*
Commande does not find the variable but the full data but export work
Find solution in parcer of word
*/

int	ft_unset(t_data *data, int index)
{
	int	status;
	int	i;

	status = CMD_OK;
	printf("IN BUITLINS\n");
	if (data->cmd[index].cmd[1][0] == '-')
	{
		error_cmd(data->cmd[index].cmd[0], "no option accepted.");
		return (CMD_EXIT);
	}
	if (data->cmd[index].cmd[1] == NULL)
		return (status);
	i = 1;
	while (data->cmd[index].cmd[i])
	{
		if (check_variable(data->cmd[index].cmd[i]) == false)
		{
			error_cmd(data->cmd[index].cmd[0], "invalid variable.");
			status = CMD_EXIT;
		}
		i++;
	}
	remove_variable(data->env, data->cmd[index].cmd + 1);
	return (status);
}
