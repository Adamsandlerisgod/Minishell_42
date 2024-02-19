/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 09:46:46 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/23 16:56:10 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_operator(int c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	return (false);
}

int	len_var(char *line)
{
	int	len_var;

	len_var = 1;
	if (!ft_isalpha(line[len_var]) && !(line[len_var] == '_')
		&& !(line[len_var] == '?'))
		return (1);
	if (line[len_var] == '?')
		return (2);
	len_var++;
	while (line[len_var] && (ft_isalnum(line[len_var]) || line[len_var] == '_'))
		len_var++;
	return (len_var);
}

int	len_operator(char *line)
{
	if (*line + 1 && (line[1] == '&' || line[1] == '|'
			|| line[1] == '<' || line[1] == '>'))
		return (2);
	return (1);
}

int	len_quote(char *line)
{
	char	quote;
	int		i;

	quote = line[0];
	i = 1;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			return (i + 1);
		i++;
	}
	if (quote == '\"')
		error_system("Error: Unclosed quote: \"");
	if (quote == '\'')
		error_system("Error: Unclosed quote: \'");
	return (0);
}
