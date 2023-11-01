/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:54:12 by whendrik          #+#    #+#             */
/*   Updated: 2023/11/01 20:15:01 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	count_quote(char *token)
{
	int	i;
	int qc;

	i = 0;
	qc = 0;
	
	while (token[i])
	{
		if (ft_isquote(token[i]))
		{
			i += lenquote(&(token[i]));
			qc += 2;
		}
		else
			i++;
	}
	return (qc);
}

char	*qt_fixed_string(char *token, int *cq, int *j)
{
	char *new_str;
	int	i;
	int quotelen;

	new_str = NULL;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(token) - 2));
	i = *j;
	while (!(ft_isquote(token[i])) && token[i])
		i++;
	quotelen = lenquote(&(token[i]));
	// printf("quotelen = %d\n", quotelen);
	if (ft_isquote(token[i]))
	{
		// printf("pre_memcpy new_str = %s : token = %s", new_str, token);
		ft_memcpy(new_str, token, i);
		// printf("memcpy 1 = %s\n", new_str);
		ft_memcpy(new_str + ft_strlen(new_str), &(token[i]) + 1, quotelen - 2);
		// printf("memcpy 2 = %s\n", new_str);
		*j = ft_strlen(new_str);
		i += quotelen;
		ft_memcpy(new_str + *j, &(token[i]), strlen(token) - i);
		// printf("memcpy 3 = %s\n", new_str);
		*cq -= 2;
	}
	return (new_str);
}

bool quote_trim(t_tokens *tokens)
{
	int quote_count;
	char *tmp_token;
	int	i;
	int	j;

	i = 0;
	while (tokens->tokens[i])
	{
		quote_count = count_quote(tokens->tokens[i]);
		printf("qc of token[i] = %d in %s\n", quote_count, tokens->tokens[i]);
		j = 0;
		while (quote_count != 0)
		{
			tmp_token = qt_fixed_string(tokens->tokens[i], &quote_count, &j);
			printf("tmp_token[%d] = %s \n", i, tmp_token);
			if (!(tokens->tokens[i]))
				/*error and free function*/
			free(tokens->tokens[i]);
			tokens->tokens[i] = tmp_token;
		}
		i++;
	}	
	return (true);
}