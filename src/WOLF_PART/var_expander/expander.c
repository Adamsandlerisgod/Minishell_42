/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:07:52 by whendrik          #+#    #+#             */
/*   Updated: 2023/12/11 21:15:35 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"


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
		if (token[i] == '$' && (token[i + 1] == '?' || ft_isalpha(token[i + 1])) && !open_single_qt)
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
	if (single_qt == 1 || double_qt == 1)
		return (0);
	while (token[i] != '\0')
	{
		if (token[i] == '\'' && !open_double_qt)
			open_single_qt = !open_single_qt;	
		if (token[i] == '\"' && !open_single_qt)
			open_double_qt = !open_double_qt;
		if (token[i] == '$' && (token[i + 1] == '?' ||
			 ft_isalpha(token[i + 1])) && !open_single_qt)
			return (1);
		i++;	
	}
	return (0);
}

bool	expandinator(t_tokens *tokens, t_data *data)
{
	int	i;
	int single_qt;
	int double_qt;
	char *pos;
	char *next_pos;
	printf("status check (expandinator) \n");
	printf("status = %d \n", data->status);
	i = 0;
	single_qt = 0;
	double_qt = 0;
	while (i < tokens->token_count)
	{

		if (is_expandable_variable(tokens->tokens[i], single_qt, double_qt))
		{
			printf("status check (expandinator 2) \n");
			printf("status = %d \n", data->status);
			pos = var_position(tokens->tokens[i], &single_qt, &double_qt);
			printf("status check (expandinator 3) \n");
			printf("status = %d \n", data->status);
			while (pos != NULL)
			{
				printf("status check (expand_vigor) \n");
				if(!(expand_var(data, &(tokens->tokens[i]), pos, &next_pos)))
					return (false);
				pos = var_position(next_pos, &single_qt, &double_qt);
			}
		}
		i++;
	}
	return (true);
}