/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_system.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 00:57:02 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 17:34:30 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_system(char *msg)
{
	ft_putstr_fd(PROMPT_R, STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_exit_msg(char *arg, char *str, int flag)
{
	if (flag == 0)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (str != NULL)
	{
		ft_putstr_fd(PROMPT_R, STDERR_FILENO);
		ft_putstr_fd("exit: ", STDERR_FILENO);
		if (arg != NULL)
		{
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
		}
		ft_putendl_fd(str, STDERR_FILENO);
	}
}

void	error_input(char *msg, char *msg_type)
{
	ft_putstr_fd(PROMPT_R, STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(msg_type, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
	g_exit_status = 258;
}

void	error_file_msg(char *file, char *msg)
{
	ft_putstr_fd(PROMPT_R, STDERR_FILENO);
	ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
