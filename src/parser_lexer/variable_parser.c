/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 15:07:52 by whendrik          #+#    #+#             */
/*   Updated: 2024/01/15 15:48:43 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	expand_var(t_data *data, char **token, char *pos, char **next_pos)
{
	char		*env_value;
	char		*new_token;
	char		*var;
	int			var_len;
	int			new_len;

	var_len = len_var(pos) - 1;
	var = ft_substr(pos, 1, var_len);
	if (var == NULL)
		return (error_system(MALLOC_ERROR), false);
	env_value = get_env_value(var, &data->env, var_len, g_exit_status);
	new_len = ft_strlen(*token) - (var_len - ft_strlen(env_value));
	new_token = (char *)ft_calloc(sizeof(char), (new_len + 1));
	ft_memcpy(new_token, *token, ft_strlen(*token) - ft_strlen(pos));
	ft_strlcat(new_token, env_value, ft_strlen(new_token)
		+ ft_strlen(env_value) + 1);
	ft_memcpy(new_token + ft_strlen(new_token), pos
		+ var_len + 1, ft_strlen(pos + var_len));
	*next_pos = new_token + (ft_strlen(*token) - ft_strlen(pos)
			+ ft_strlen(env_value));
	free(var);
	free(env_value);
	free(*token);
	*token = new_token;
	return (true);
}

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
		if (token[i] == '$' && (token[i + 1] == '?'
				|| ft_isalpha(token[i + 1])) && !open_single_qt)
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

static bool	is_expandable_variable(char *token, int single_qt, int double_qt)
{
	int	i;
	int	open_single_qt;
	int	open_double_qt;

	i = 0;
	open_single_qt = 0;
	open_double_qt = 0;
	double_qt = 0;
	if (single_qt == 1)
		return (false);
	while (token[i] != '\0')
	{
		if (token[i] == '\'' && !open_double_qt)
			open_single_qt = !open_single_qt;
		if (token[i] == '\"' && !open_single_qt)
			open_double_qt = !open_double_qt;
		if (token[i] == '$' && (token[i + 1] == '?'
				|| ft_isalpha(token[i + 1])) && !open_single_qt)
			return (true);
		i++;
	}
	return (false);
}

static bool	expandinator(t_data *data, t_tokens *tokens, int i)
{
	char	*next_pos;
	char	*pos;
	int		single_qt;
	int		double_qt;

	single_qt = 0;
	double_qt = 0;
	if (is_expandable_variable(tokens->tokens[i], single_qt, double_qt))
	{
		pos = var_position(tokens->tokens[i], &single_qt, &double_qt);
		while (pos != NULL)
		{
			if (is_expandable_variable(pos, single_qt, double_qt))
			{
				if (!(expand_var(data, &(tokens->tokens[i]), pos, &next_pos)))
					return (false);
			}
			pos = var_position(next_pos, &single_qt, &double_qt);
		}
	}
	return (true);
}

bool	variable_parser(t_tokens *tokens, t_data *data)
{
	int		i;

	i = 0;
	while (i < tokens->token_count)
	{
		if (!(expandinator(data, tokens, i)))
			return (false);
		i++;
	}
	return (true);
}
