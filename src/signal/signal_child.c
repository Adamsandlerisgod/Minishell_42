/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 14:59:15 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 17:24:22 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quit(int signum)
{
	if (signum == SIGQUIT)
		exit(131);
}

void	sigint_child_handler(int signum)
{
	if (signum == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(130);
	}
}

void	open_quit_signal_on_valid_cmd(t_data *data, int index)
{
	if (!ft_strncmp(data->cmd[index].cmd[0], "cat", 3) || \
		!ft_strncmp(data->cmd[index].cmd[0], "/bin/cat", 8) || \
		(!ft_strncmp(data->cmd[index].cmd[0], "grep", 4) && \
		data->cmd[index].cmd[1] != NULL) || \
		(!ft_strncmp(data->cmd[index].cmd[0], "/usr/bin/grep", 13) && \
		data->cmd[index].cmd[1] != NULL) || \
		(!ft_strncmp(data->cmd[index].cmd[0], "awk", 3) && \
		data->cmd[index].cmd[1] != NULL) || \
		(!ft_strncmp(data->cmd[index].cmd[0], "/usr/bin/awk", 12) && \
		data->cmd[index].cmd[1] != NULL) || \
		(!ft_strncmp(data->cmd[index].cmd[0], "wc", 2) && \
		data->cmd[index].cmd[1] == NULL) || \
		(!ft_strncmp(data->cmd[index].cmd[0], "/usr/bin/wc", 11) && \
		data->cmd[index].cmd[1] == NULL))
	{
		data->sa_q.sa_handler = handle_quit;
		sigaction(SIGQUIT, &data->sa_q, NULL);
	}
}
