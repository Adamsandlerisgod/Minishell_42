/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:06:30 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/18 18:52:14 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	ft_istoken(int c)
{
	if (!(ft_isoptr(c)) && !(ft_isspace(c)))
		return (true);
	return (false);
}

bool	ft_isoptr(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int	lenquote(char *line)
{
	int i;
	char c;

	c = line[0];
	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (i + 1);
		i++;
	}
	if (c == '\"')
		printf("quote error\n");
		// quote_error(2);
	if (c == '\'')
		printf("quote error\n");
		// quote_error(1);
	return (0);
}

int	lenvar(char *line)
{
	int i;

	i = 1;
	if (!ft_isalpha(line[i]) && !(line[i] == '_'))
		return (0);
	i++;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}
