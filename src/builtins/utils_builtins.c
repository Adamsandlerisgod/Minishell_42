/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:27:10 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/11 21:26:57 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	len_variable(char *var)
{
	int	i;

	i = 0;
	while (var[i] != '=')
		i++;
	return (i + 1);
}

bool	check_variable(char *var)
{
	int	i;

	i = 0;
	printf("IN WHILE LOOP check_variable 1 \n");
	if (ft_isdigit(var[i]) || var[i] == '_')
		return (false);
	i++;
	while (var[i] != '=' && var[i] != '\0')
	{
		printf("IN WHILE LOOP check_variable 2 \n");
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

void	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
}

void	add_variable(t_env *tmp_env, char *var)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		error_system("malloc failed\n");
	new->name = ft_strdup(var);
	new->next = NULL;
	tmp_env->next = new;
}
