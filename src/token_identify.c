/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:46:44 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/20 20:10:45 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tk_type token_class(char *token, t_tk_type pre)
{
	if (*token == '<' || *token == '>')
		return (e_rdrt);
	else if (*token == '|')
		return (e_pipe);
	else if (pre == e_rdrt)
		return (e_filename);
	else
		return (e_argument);
}

bool	token_identify(t_tokens *tokens)
{
	t_tk_type	*type;
	int			i;
	int			j;
	int			pipe_num;
	int			arg_num;

	i = 0;
	j = 0;
	pipe_num = 0;
	type = (t_tk_type *)malloc(sizeof(t_tk_type) * (tokens->token_count + 1));
	if (!type)
		return (false);
	while (i < tokens->token_count)
	{
		if (i == 0)
			type[i] = token_class(tokens->tokens[i], e_void);
		else
			type[i] = token_class(tokens->tokens[i], type[i - 1]);
		if (type[i] == e_pipe)
			pipe_num++;
		i++;
	}
	tokens->token_type = type;
	return (true);
}