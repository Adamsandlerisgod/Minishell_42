/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:29 by jhurpy            #+#    #+#             */
/*   Updated: 2023/11/01 20:12:52 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

// Testing Remove later V
// char	**env_array(t_env *env)
// {
// 	t_env	*tmp;
// 	char	**ev;
// 	int		len_env;

// 	tmp = env;
// 	len_env = 0;
// 	while (tmp)
// 	{
// 		len_env++;
// 		tmp = tmp->next;
// 	}
// 	tmp = env;
// 	ev = (char **)malloc(sizeof(char *) * (len_env + 1));
// 	if (ev == NULL)
// 	{
// 		error_system("malloc failed\n");
// 		return (NULL);
// 	}
// 	ev[len_env] = NULL;
// 	while (len_env--)
// 	{
// 		ev[len_env] = ft_strdup(tmp->name);
// 		tmp = tmp->next;
// 	}
// 	return (ev);
// }
// Testing Remove later ^

void print_environment(t_env *env) {
    t_env *tmp = env;

	if (tmp == NULL)
		printf("THis bitch empy \n");
    while (tmp) {
        printf("Environment Variable: %s\n", tmp->name);
        tmp = tmp->next;
    }
}

// static void	init_variable(t_env *tmp, char *env)
// {
// 	int		i;
// 	char	*tmp_i;

// 	i = 0;
// 	if (ft_strncmp(env, "SHLVL=", 6) == 0)
// 	{
// 		i = ft_atoi(env + 6);
// 		tmp_i = ft_itoa(i + 1);
// 		tmp->name = ft_strjoin("SHLVL=", tmp_i);
// 		free(tmp_i);
// 	}
// 	else
// 		tmp->name = ft_strdup(env);
// }

// static void create_new_env(t_env **my_env, char **env)
// {
//     t_env *tmp = NULL; // Temporary pointer for iterating through the list

//     while (*env)
//     {
// 		if (ft_strncmp(*env, "OLDPWD=", 7) == 0)
// 		{
//         	if (tmp == NULL)
//         	{
// 				*my_env = (t_env *)malloc(sizeof(t_env)); // Create the first node
// 				if (*my_env == NULL)
//                 	ft_putstr_fd("Error: Memory allocation failed\n", /*STDERR_FILENO*/ 2);
//             	tmp = *my_env;
//         	}
//         	else
//         	{
//             	tmp->next = (t_env *)malloc(sizeof(t_env)); // Create a new node
//             	if (tmp->next == NULL)
// 				ft_putstr_fd("Error: Memory allocation failed\n", /*STDERR_FILENO*/ 2);
// 				tmp = tmp->next;
//         	}
//         	init_variable(tmp, *env);
//         	tmp->next = NULL;
//         	env++;
// 		}
// 		env++;
//     }
// }
t_env *create_env_node(char *name) {
    t_env *node = (t_env *)malloc(sizeof(t_env));
	
	if (node) {
        node->name = strdup(name);
        node->next = NULL;
    }
    return (node);
}

void add_env_variable(t_env **env, char *name) {
    if (env == NULL)
        return;
    t_env *node = create_env_node(name);
    if (node == NULL)
        return;
    node->next = *env;
    *env = node;
}

t_env *char_array_to_linked_list(char **env) {
    t_env *myenv = NULL;
    if (env == NULL)
        return myenv;

    int i = 0;
    while (env[i] != NULL) {
        add_env_variable(&myenv, env[i]);
        i++;
    }

    return myenv;
}

/*
The function set_env is used to set the environment variable when starting
the minishell.
*/

t_env	*set_env(char **env)
{
	t_env	*my_env = NULL;

	printf("Inshallah\n");
	if (!env)
	{
		ft_putstr_fd("Error: env is NULL\n", /*STDERR_FILENO*/ 2);
		// exit (CMD_ERROR);
	}
	my_env = char_array_to_linked_list(env);
	// create_new_env(&my_env, env);
	print_environment(my_env);
	return (my_env);
}

// void print_environment(t_env *env) {
//     t_env *tmp = env;

//     while (tmp) {
//         printf("Environment Variable: %s\n", tmp->name);
//         tmp = tmp->next;
//     }
// }