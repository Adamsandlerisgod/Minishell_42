/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:34:29 by whendrik          #+#    #+#             */
/*   Updated: 2024/01/23 20:14:12 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_command(int c)
{
	if (!(ft_isquote(c)) && !(is_operator(c)))
		return (true);
	return (false);
}

static int	len_command(char *line)
{
	int	i;

	i = 1;
	while (line[i] && is_command(line[i]))
		i++;
	return (i);
}

bool	check_line(char *line)
{
	int	len_line;

	while (line != NULL && *line != '\0')
	{
		len_line = 0;
		while (*line && ft_isspace(*line))
			line++;
		if (!(*line))
			break ;
		else if (ft_isquote(*line))
			len_line = len_quote(line);
		else if (is_operator(*line))
			len_line = len_operator(line);
		else if ((*line) == '$')
			len_line = len_var(line);
		else if (is_command(*line))
			len_line = len_command(line);
		if (len_line == 0)
			return (false);
		line += len_line;
	}
	return (true);
}
