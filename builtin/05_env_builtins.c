/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_env_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:03:14 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 17:21:46 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	env_builtins(t_cmd *cmd, char **env, int i)
{
	if (cmd[i].cmd[1])
	{
		ft_putendl_fd("minishell: env: no option accepted", 2);
		ft_putendl_fd("env: usage: env", 2);
		return (1);
	}
	while (*env)
	{
		if (ft_strchr(*env, '='))
			ft_putendl_fd(*env, 1);
		env++;
	}
	return (0);
}
