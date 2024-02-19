/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 20:05:12 by whendrik          #+#    #+#             */
/*   Updated: 2024/01/24 02:03:12 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	order_error_check(t_tokens *tokens, int i)
{
	t_tk_type	type;
	t_tk_type	prev;

	prev = e_void;
	type = tokens->token_type[i];
	if (i > 0)
		prev = tokens->token_type[i - 1];
	if ((prev == e_pipe && type == e_pipe) || (prev == e_rdrt
			&& type == e_rdrt) || (prev == e_rdrt && type == e_pipe))
		return (error_input(SYNTAX_ERROR, tokens->tokens[i]), false);
	return (true);
}

static bool	check_type_token(t_tokens *tokens, int nb_token)
{
	int	last_char;

	last_char = 0;
	if (tokens->token_type[0] == e_pipe)
	{
		error_input(SYNTAX_ERROR, tokens->tokens[0]);
		return (false);
	}
	else if ((tokens->token_type[nb_token] == e_pipe)
		|| (tokens->token_type[nb_token] == e_rdrt))
	{
		last_char = ft_strlen(tokens->tokens[nb_token]) - 1;
		error_input(SYNTAX_ERROR, &tokens->tokens[nb_token][last_char]);
		return (false);
	}
	return (true);
}

bool	token_syntax(t_tokens *tokens)
{
	int	i;
	int	nb_token;

	i = 0;
	nb_token = tokens->token_count - 1;
	if (check_type_token(tokens, nb_token) == false)
		return (false);
	while (i <= nb_token)
	{
		if (!(order_error_check(tokens, i)))
			return (false);
		i++;
	}
	return (true);
}
