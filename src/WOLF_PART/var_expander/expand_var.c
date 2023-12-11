/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:18:12 by whendrik          #+#    #+#             */
/*   Updated: 2023/12/11 22:13:17 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char *get_env_value(char *var, t_env **env, int var_len, int status)
{
	t_env	*env_list;
	char	*name_value;

	name_value = NULL;
	env_list = *env;
	while (env_list != NULL)
	{
		if (ft_strncmp(var, "?", 1) == 0)
		{	
			printf("status in getenvvalue = %d \n", status);
			name_value = ft_strdup(ft_itoa(status));
			printf("name value = %s \n", name_value);
			// return (name_value);
			return (name_value);
		}
		else if (ft_strncmp(var, env_list->name, var_len) == 0 
			&& ft_strncmp("=", env_list->name + var_len, 1) == 0)
		{
			name_value = ft_strdup(env_list->name + var_len + 1);
			return (name_value);
		}
		env_list = env_list->next;
	}
	name_value = ft_strdup("");
	return (name_value);
}

bool	expand_var(t_data *data, char **token, char *pos, char **next_pos)
{
	char *env_value;
	char *var;
	int	var_len;
	char *new_token;
	int new_len;

	
	var_len = lenvar(pos) - 1;
	var = (char *)ft_calloc(var_len + 1, sizeof(char));
	printf("status check (expand_var 2) \n");
	// if (!(var_check(var)))
	// 	return (0);
	/*There's probably a more efficient way using realloc*/
	/*Make on for expanding var + one for expanding brackets or $?*/
	printf("var len = %d  && pos + 1 = %c\n", var_len, pos[1]);
	ft_memcpy(var, pos + 1, var_len);
	printf("status check (expand_var 1) \n");
	printf("status = %d \n", data->status);
	env_value = get_env_value(var, &data->env, var_len, data->status);
	new_len = ft_strlen(*token) - (var_len - ft_strlen(env_value));
	new_token = (char *)ft_calloc(sizeof(char), (new_len + 1));
	ft_memcpy(new_token, *token, ft_strlen(*token) - ft_strlen(pos));
	ft_strlcat(new_token, env_value, strlen(new_token) + strlen(env_value) + 1);
	ft_memcpy(new_token + ft_strlen(new_token), pos + var_len + 1, ft_strlen(pos + var_len));
	*next_pos = new_token + ft_strlen(env_value);
	free(var);
	free(env_value);
	// free(*token);
	*token = new_token;
	// free(new_token);
	return (1);
}