/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:07:52 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/26 15:25:54 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


/*See where you can simplify*/
static char	*var_position(char *token, int *s_open, int *d_open)
{
	int	open_single_qt;
	int	open_double_qt;
	int	i;

	i = 0;
	open_single_qt = *s_open;
	open_double_qt = *d_open;
	while (token[i] != '\0')
	{
		if (token[i] == '\'' && !open_double_qt)
			open_single_qt = !open_single_qt;	
		if (token[i] == '\"' && !open_single_qt)
			open_double_qt = !open_double_qt;
		if (token[i] == '$' && (token[i + 1] == '?' | ft_isalpha(token[i + 1])) && !open_single_qt)
		{
			*s_open = open_single_qt;
			*d_open = open_double_qt;
			return (&token[i]);
		}
		i++;
	}
	*s_open = open_single_qt;
	*d_open = open_double_qt;
	return (NULL);
}

bool	is_expandable_variable(char *token, int single_qt, int double_qt)
{
	int i;
	int open_single_qt;
	int open_double_qt;

	i = 0;
	open_single_qt = 0;
	open_double_qt = 0;
	
	{

		while (token[i] != '\0')
		{
			if (token[i] == '\'' && !open_double_qt)
				open_single_qt = !open_single_qt;	
			if (token[i] == '\"' && !open_single_qt)
				open_double_qt = !open_double_qt;
			if (token[i] == '$' && (token[i + 1] == '?' | ft_isalpha(token[i + 1])) && !open_single_qt)
				return (1);
			i++;	
		}
	}
}

bool	expandinator(t_tokens	*tokens, t_list *env)
{
	int	i;
	int single_qt;
	int double_qt;
	char *pos;
	char *next_pos;

	i = 0;
	single_qt = 0;
	double_qt = 0;

	while (i < tokens->cmd_count)
	{
		if (is_expandable_variable(tokens->tokens[i], single_qt, double_qt))
		{
			pos = var_position(tokens->tokens[i], &single_qt, &double_qt);
			while (pos != NULL)
			{
				if(!(expand_var(env, tokens->tokens[i], &pos, &next_pos)))
					return (false);
				next_pos = var_position(next_pos, &single_qt, &double_qt);
			}
		}
		i++;
	}
	get_env_string()
}