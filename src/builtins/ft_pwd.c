/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:06 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/28 15:38:40 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	ft_pwd(t_data *data, int index)
{
	char	*pwd[PATH_MAX];

	if (data->cmd[index].cmd[1][0] == '-')
	{
		// Error message management; no option accepted + usage
		return (CMD_EXIT);
	}
	getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
	{
		// Error message management; getcwd failed
		return (CMD_ERROR);
	}
	ft_putendl_fd(pwd, STDOUT_FILENO);
	free(pwd);
	return (CMD_OK);
}
