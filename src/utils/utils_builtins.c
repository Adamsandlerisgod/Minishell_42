/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:27:10 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 01:40:03 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(char **env, int flag)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (flag == 1)
			printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
	g_exit_status = CMD_OK;
}

bool	check_long_long(char *str)
{
	char	*tmp;

	if (str[0] == 45 && ft_strlen(str) <= 20)
	{
		if (ft_strlen(str) == 20 && str[1] == 57)
		{
			tmp = ft_substr(str, 2, 19);
			if (ft_atoll(tmp) > 223372036854775808)
				return (false);
		}
		return (true);
	}
	else if (ft_strlen(str) <= 19)
	{
		if (ft_strlen(str) == 19 && str[0] == 57)
		{
			tmp = ft_substr(str, 1, 18);
			if (ft_atoll(tmp) > 223372036854775807)
				return (false);
		}
		return (true);
	}
	return (false);
}

char	*get_home_oldpwd_path(char *var, t_data *data)
{
	char	*path;

	path = NULL;
	if (ft_strncmp("OLDPWD", var, 7) == 0
		|| ft_strncmp("HOME", var, 7) == 0)
	{
		path = get_env_value(var, &data->env, ft_strlen(var), 0);
		if (!path)
		{
			error_cmd_msg("cd", var, NO_VAR);
			g_exit_status = CMD_ERROR;
		}
		if (var != NULL)
			free(var);
	}
	return (path);
}
