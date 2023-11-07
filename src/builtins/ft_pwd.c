/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:06 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/07 17:43:12 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_data *data, int index)
{
	char	*pwd[PATH_MAX];

	if (data->cmd[index].cmd[1][0] == '-')
	{
		error_cmd(data->cmd[index].cmd[0], "no option accepted.");
		return (CMD_EXIT);
	}
	getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
	{
		error_system("pwd failed\n", errno);
		return (CMD_ERROR);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (CMD_OK);
}
