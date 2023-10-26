/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:22:35 by whendrik          #+#    #+#             */
/*   Updated: 2023/10/11 13:53:31 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
// #include "../../includes/minishell.h" // Include the necessary header file
typedef struct s_env
{
	char	*name;
	struct s_env	*next;
}		t_env;
// Mocked function for getting environment values
char *get_env_value(char *var, t_env **env, int var_len) {
    // Simulate fetching the environment value based on the variable name
    if (strcmp(var, "HOME") == 0) {
        return strdup("/home/user");
    }
    return strdup(""); // Return NULL for undefined variables
}

// char *get_env_value(char *var, t_env **env, int var_len)
// {
// 	t_env	*env_list;
// 	char	*name_value;

// 	name_value = NULL;
// 	env_list = *env;
// 	while (env_list->next != NULL)
// 	{
// 		if (ft_strncmp(var + 1, env_list->name, var_len - 1) == 0)
// 		{
// 			name_value = ft_strdup(env_list->name + var_len + 1);
// 			return (name_value);
// 		}
// 		env_list = env_list->next;
// 	}

// }
int	ft_isalpha(int c)
{
	return ((c <= 122 && c >= 97) || (c <= 90 && c >= 65));
}

int	ft_isdigit(int c)
{
	return (c <= 57 && c >= 48);
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	lenvar(char *line)
{
	int i;

	i = 0;
	if (!(ft_isalpha(line[i])) && !(line[i] == '_'))
		return (0);
	i++;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	return (i);
}

bool	expand_var(t_env *env, char **token, char *pos, char **next_pos)
{
	char *env_value;
	char *var;
	int	var_len;
	char *new_token;
	int new_len;
	char *result;

	printf("bitch\n");
	result = *token;
	var_len = lenvar(pos + 1);
	printf("var_len = %d \n", var_len);

	var = (char *)calloc(var_len + 1, sizeof(char));
	memcpy(var, pos + 1, var_len);
	printf("var = %s \n", var);
	// if (!(var_check(var)))
	// 	return (0);
	/*There's probably a more efficient way using realloc*/
	/*Make one for expanding var + one for expanding brackets or $?
	Make one for expanding var not in env*/
	env_value = get_env_value(var, &env, var_len);
	/*make one for if no value is returned*/
	printf("env_value = %s \n", env_value); 
	new_len = strlen(*token) - (var_len - strlen(env_value));
	printf("new_len = %d \n", new_len);
	new_token = (char *)calloc(sizeof(char), (new_len + 1));
	// (char *)realloc(token, sizeof(char) * (new_len + 1));
	printf("alloc success\n");
	memcpy(new_token, *token, strlen(*token) - strlen(pos));
	printf("memcpy1 = %s\n", new_token);
	strlcat(new_token, env_value, strlen(new_token) + strlen(env_value) + 1);
	printf("strlcat = %s\n", new_token);
	memcpy(new_token + strlen(new_token), (pos + var_len + 1), strlen(pos + var_len));
	printf("strlcat2 = %s\n", new_token);
	*next_pos = new_token + strlen(env_value);
	free(var);
	free(env_value);
	*token = new_token;
	return (true);
}

int main() {
	printf("fuck\n");

    // Initialize the environment linked list with a single variable
    t_env *env = malloc(sizeof(t_env));
    env->name = strdup("HOME");
    env->next = NULL;
printf("fuck3\n");
    // Input token with an environment variable ${HOME}
    char *token = strdup("This is your $HOME directory: $HOMER/documents fehkjhkejfbahfbfef $");

    // Initialize variables for position and the next position
	int i = 0;

    while (token[i] != '$')
		i++;
	char *pos = &(token[i]);
    char *next_pos = NULL;
printf("pos = %s\n", pos);

    // Perform variable expansion
    
printf("fuck2\n");
int x = 0;
 while (x++ < 2) {
    if((expand_var(env, &token, pos, &next_pos)))
        printf("Original Token: %s\n", token);
        // printf("Expanded Token: %s\n", expanded_token);
	i++;
	while (token[i] != '$')
		i++;
	pos = &(token[i]);
    
    }
 
    // Clean up: Free memory
    free(env->name);
    free(env);
    
    return 0;
}
