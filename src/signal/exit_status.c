/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:28:01 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 23:54:19 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_status(int status)
{
	if (WIFSIGNALED(status))
		g_exit_status = WTERMSIG(status) + 128;
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}
