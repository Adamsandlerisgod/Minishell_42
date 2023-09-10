/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:15:04 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 17:36:39 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *str1, char *str2)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putendl_fd(str2, STDERR_FILENO);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	exit(EXIT_FAILURE);
}
