/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:34:29 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/11 20:09:19 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	ft_iscmd(int c)
{
	if (!(ft_isquote(c)) && !(ft_isoprt(c)))
		return (true);
	return (false);
}

bool	isspecial(int c)
{
	if (c == '$' || c == '#' || c == '@' || c == '-'
			|| c == '!' || c == '*')
		return (true);
	return (false);
}

int	lenvar(char *line)
{
	int i;

	i = 0;
	if (!ft_isalpha(line[i]) && !(line[i] == '_'))
		return (0);
	i++;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}

int	lendollar(char *line)
{
	int i;

	i = 1;
	if (!(line[i]))
		return (1);
	else if (line[i] == '?')
		i++;
	else if (ft_isdigit(line[i]))
		i++;
	else if (isspecial(line[i]))
	 	i++;
	else if (ft_isalpha(line[i] || line[i] == '_'))
		i += lenvar(&line[i]);
	return (i);
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
	if (c == "\"")
		quote_error(2);
	if (c == "\'")
		quote_error(1);
	return (0);
}



int	lenoptr(char *line)
{
	if (*line + 1 && (line[1] == '&' || line[1] == '|' || line[1] == '<' || line[1] == '>'))
		return (2);
	return (1);
}

int	lencmd(char *line)
{
	int i;

	i = 1;
	while (line[i] && ft_iscmd(line[i]))
		i++;
	return (i);
}

/*Check for unclosed quotes & Variables e.g. $$ -$ */
bool	lexer(char *line)
{
	int i;

	i = 0;
	if (!(*line))
		return (false);
	while(*line)
	{
		while (*line && ft_isspace(*line))
			line++;
		if (!(*line))
			break ;
		else if(ft_isquote(*line))
			i = lenquote(line);
		else if(ft_isoprt(*line))
			i = lenoptr(line);
		else if ((*line) == '$')
			i = lenvar(line);
		else if (ft_iscmd(*line))
			i = lencmd(line);
		if (i = 0)
			return (false);
		else
			line += i;
	}
	return (true);
}
