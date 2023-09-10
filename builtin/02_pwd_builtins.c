/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_pwd_builtins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:03:26 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 19:22:33 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

int	pwd_builtins(t_cmd *cmd, int i)
{
	int		status;
	char	*pwd[1024];

	if (cmd[i].cmd[1][0] == '-')
	{
		msg_cmd("minishell: pwd:", cmd[i].cmd[1],
			": option not accepted", 2);
		msg_cmd("pwd: usage: pwd", NULL, NULL, 2);
		return (1);
	}
	getcwd(pwd, 1024);
	if (pwd == NULL)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (status);
}
