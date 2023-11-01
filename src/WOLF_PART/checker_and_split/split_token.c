/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:14:00 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/01 20:13:50 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

/*&& included for bonus
int	len_token(char *line)
{
	int		i;

	i = 0;
	if (ft_istoken(line[i]) || (line[i] == '&' && line[i + 1] != '&'))
	{
		if (line[i] == '&' && line[i + 1] != '&')
				i++;
		while ((ft_istoken(line[i]) || (line[i] == '&' && line[i + 1] != '&')) && line[i])
		{
			if (line[i] == '&' && line[i + 1] != '&')
				i++;
			if (ft_isquote(line[i]))
				i += lenquote(&line[i]);
			else
				i++;
		}
	}
	else if (ft_isoptr(line[i]))
		i += lenoptr(&line[i]);
	return (i);
}
*/
int	len_token(char *line)
{
	int		i;

	i = 0;
	if (ft_istoken(line[i]))
	{
		while ((ft_istoken(line[i]) && line[i]))
		{
			if (ft_isquote(line[i]))
				i += lenquote(&line[i]);
			else
				i++;
		}
	}
	else if (ft_isoptr(line[i]))
		i += lenoptr(&line[i]);
	return (i);
}

int	token_count(char *line)
{
	int	tc;
	int	i;

	tc = 0;
	i = 0;
	if (!line)
		return (tc);
	
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!(line[i]))
			return (tc);
		if(ft_istoken(line[i]))
			i += len_token(&line[i]);
		else if(ft_isoptr(line[i]))
			i += lenoptr(&line[i]);
		tc++;
	}
	return (tc);
}


char **token_split(char *line, int tc)
{
	int		i;
	int		j;
	int		k;
	char	**tokens;

	i = 0;
	j = 0;
	k = 0;
	tokens = (char **)malloc(sizeof(char *) * (tc + 1));
	while (j < tc)
	{
		while (ft_isspace(line[i]))
			i++;
		k = len_token(&line[i]);
		tokens[j] = (char *)malloc(sizeof(char) * (k + 1));
		ft_memcpy(tokens[j], &line[i], k);
		tokens[j][k] = '\0';
		i += k;
		j++;
	}
	tokens[tc] = NULL;
	return (tokens);
}

int split_token(char *line, t_tokens *stuff)
{
	int tc;
	char **tokens;
	// char **line_s;
	tc = token_count(line);
	printf("tc = %d \n", tc);
	// line_s = split_line(line, tc);
	tokens = (char **)malloc(sizeof(char *) * (tc + 1));
	if (tc == 0)
		return (false);
	tokens = token_split(line, tc);
	stuff->token_count = tc;
	stuff->tokens = tokens;
	return (true);
}

/*Test works great*/
	// int i = 0;
	// while(i < tc)
	// {
	// 		printf("tokens[%d] = %s \n", i, tokens[i]);
	// 		i++;
	// }