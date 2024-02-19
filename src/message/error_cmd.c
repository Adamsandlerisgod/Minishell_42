/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:11:39 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/22 01:03:40 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_cmd(char *cmd, char *msg)
{
	ft_putstr_fd(PROMPT_R, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_cmd_var(char *cmd, char *msg, char *str)
{
	ft_putstr_fd(PROMPT_R, STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd("`", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\': ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	error_cmd_msg(char *cmd1, char *cmd2, char *msg)
{
	ft_putstr_fd(PROMPT_R, STDERR_FILENO);
	ft_putstr_fd(cmd1, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd2, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
}
