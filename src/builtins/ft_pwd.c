/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:06 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/10 23:27:01 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_data *data, int index)
{
	char	pwd[PATH_MAX];

	if (data->cmd[index].cmd[1] != NULL)
	{
		if (data->cmd[index].cmd[1][0] == '-')
		{
			error_cmd(data->cmd[index].cmd[0], "no option accepted.");
			return (CMD_EXIT);
		}
	}
	getcwd(pwd, PATH_MAX);
	ft_putendl_fd(pwd, STDOUT_FILENO);
	return (CMD_OK);
}
