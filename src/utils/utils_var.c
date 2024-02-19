/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 01:23:30 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/24 14:05:56 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_path_cmd(char **path_array, char *command)
{
	char	*tmp_path;
	char	*path;
	int		i;

	i = 0;
	while (path_array[i] != NULL)
	{
		tmp_path = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(tmp_path, command);
		if (tmp_path != NULL)
			free(tmp_path);
		if (access(path, F_OK) == 0)
			break ;
		if (path != NULL)
			free(path);
		path = NULL;
		i++;
	}
	return (path);
}

int	len_variable(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i + 1);
}

void	add_variable(t_env *tmp_env, char *var)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		error_system(MALLOC_ERROR);
	new->name = ft_strdup(var);
	new->next = NULL;
	tmp_env->next = new;
}

bool	check_variable(char *var)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[i]) || var[i] == '_')
		return (false);
	if (!ft_isalpha(var[i]))
		return (false);
	i++;
	while (var[i] != '=' && var[i] != '\0')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
