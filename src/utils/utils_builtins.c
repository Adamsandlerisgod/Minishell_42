/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:27:10 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 13:31:20 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	len_variable(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i + 1);
}

bool	check_var(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]))
		return (false);
	while (var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	print_env(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		ft_putendl_fd(tmp_env->name, 1);
		tmp_env = tmp_env->next;
	}
}
