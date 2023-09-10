/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:24:23 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/11 06:51:55 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

void	msg_cmd(char *arg1, char *arg2, char *arg3, int fd)
{
	ft_putstr_fd(arg1, fd);
	ft_putstr_fd(arg2, fd);
	ft_putendl_fd(arg3, fd);
}
