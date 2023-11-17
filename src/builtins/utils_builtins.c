/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:27:10 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/16 17:09:20 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_variable(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i + 1);
}

bool	check_variable(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) || var[i] == '_')
		return (false);
	i++;
	while (var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	printf("env[%d] = %s \n", i, env[i]);
	while (env[i])
	{
		printf("env[%d] = %s \n", i, env[i]);
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
}
