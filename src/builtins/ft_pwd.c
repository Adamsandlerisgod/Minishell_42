/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:16:06 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/25 14:57:09 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

int	ft_pwd(t_cmd *cmd, int index)
{
	char	*pwd[PATH_MAX];

	if (cmd[index].cmd[1][0] == '-')
	{
		// Error message management; no option accepted + usage
		return (CMD_ERROR);
	}
	getcwd(pwd, PATH_MAX);
	if (pwd == NULL)
	{
		// Error message management; getcwd failed
		return (CMD_ERROR);
	}
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (CMD_OK);
}
