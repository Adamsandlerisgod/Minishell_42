/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:14:00 by whendrik          #+#    #+#             */
/*   Updated: 2024/01/18 17:50:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_token(int c)
{
	if (!(is_operator(c)) && !(ft_isspace(c)))
		return (true);
	return (false);
}

static int	len_token(char *line)
{
	int		i;

	i = 0;
	if (is_token(line[i]))
	{
		while ((is_token(line[i]) && line[i]))
		{
			if (ft_isquote(line[i]))
				i += len_quote(&line[i]);
			else
				i++;
		}
	}
	else if (is_operator(line[i]))
		i += len_operator(&line[i]);
	return (i);
}

static int	token_count(char *line)
{
	int	nb_tokens_cmd;
	int	i;

	nb_tokens_cmd = 0;
	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!(line[i]))
			return (nb_tokens_cmd);
		if (is_token(line[i]))
			i += len_token(&line[i]);
		else if (is_operator(line[i]))
			i += len_operator(&line[i]);
		nb_tokens_cmd++;
	}
	return (nb_tokens_cmd);
}

static char	**token_split(char *line, int nb_tokens_cmd)
{
	char	**tokens;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	tokens = (char **)malloc(sizeof(char *) * (nb_tokens_cmd + 1));
	if (tokens == NULL)
		return (error_system(MALLOC_ERROR), NULL);
	while (j < nb_tokens_cmd)
	{
		while (ft_isspace(line[i]))
			i++;
		len = len_token(&line[i]);
		tokens[j] = ft_substr(line, i, len);
		i += len;
		j++;
	}
	tokens[nb_tokens_cmd] = NULL;
	return (tokens);
}

int	split_tokens(char *line, t_tokens *token_cmd)
{
	char	**tokens;
	int		nb_tokens_cmd;

	tokens = NULL;
	nb_tokens_cmd = token_count(line);
	if (nb_tokens_cmd == 0)
		return (false);
	tokens = token_split(line, nb_tokens_cmd);
	token_cmd->token_count = nb_tokens_cmd;
	token_cmd->tokens = tokens;
	return (true);
}
