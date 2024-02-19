/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:06 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 18:54:52 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_pwd show the actual path.
The command do not take any option.
*/

void	ft_pwd(t_data *data, int index)
{
	char	pwd[PATH_MAX];

	if (data->cmd[index].cmd[1] != NULL)
	{
		if (data->cmd[index].cmd[1][0] == '-')
		{
			error_cmd_msg("pwd", data->cmd[index].cmd[1], NO_OPTION);
			g_exit_status = CMD_ERROR;
		}
	}
	getcwd(pwd, PATH_MAX);
	g_exit_status = CMD_OK;
	printf("%s\n", pwd);
}
