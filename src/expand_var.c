/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:18:12 by whendrik          #+#    #+#             */
/*   Updated: 2023/09/26 18:26:51 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *get_env_value(char *var, t_env **env, int var_len)
{
	t_env	*env_list;
	char	*name_value;

	env_list = *env;
	while (env_list->next != NULL)
	{
		if (ft_strncmp(var + 1, env_list->name, var_len - 1) == 0)
		{
			name_value = ft_strdup(env_list->name + var_len + 1);
			return (name_value);
		}
		env_list = env_list->next;
	}

}

bool	expand_var(t_list *env, char *token, char *pos, char *next_pos)
{
	char *env_value;
	char *var;
	int	var_len;
	char *new_token;
	int new_len;

	var_len = len_var(pos);
	var = (char *)ft_calloc(var_len + 1, sizeof(char));
	ft_memcpy(var, pos, var_len);
	if (!(var_check(var)))
		return (0);
	/*There's probably a more efficient way using realloc*/
	/*Make on for expanding var + one for expanding brackets or $?*/
	env_value = get_env_value(var, &env, var_len);
	new_len = ft_strlen(token) - (var_len - ft_strlen(env_value));
	new_token = (char *)ft_realloc(token, sizeof(char) * (new_len + 1));
	ft_memcpy(new_token, token, ft_strlen(token) - ft_strlen(pos));
	ft_memcpy(new_token, env_value, ft_strlen(env_value));
	ft_memcpy(new_token, pos + var_len, ft_strlen(pos) - var_len);
	free(var);
	free(env_value);
	return (new_token);
}