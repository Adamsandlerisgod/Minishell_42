/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:51 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/16 17:06:53 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function env_builtins is used to print the environment variables.
Check if the command has an option or an argument.
*/

int	ft_env(t_data *data, char **env, int index)
{
	printf("ft_env \n");
	if (data->cmd[index].cmd[1])
	{
		error_cmd(data->cmd[index].cmd[0], "no option or argument accepted.");
		return (CMD_EXIT);
	}
	printf("ft_env 1\n");
	print_env(env);
	printf("ft_env 2\n");
	return (CMD_OK);
}
