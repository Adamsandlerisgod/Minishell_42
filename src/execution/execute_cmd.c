/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:44:00 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 00:03:47 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static char	**get_cmd(char *av)
{
	char	**cmd;

	if (av == NULL || ft_strlen(av) == 0)
		exit_error("minishell: ", "command not found"); // TODO: error message
	cmd = ft_split(av, ' ');
	if (cmd == NULL)
		exit_error("minishell", "malloc failed "); // TODO: error message
	if (cmd[0] == NULL)
		exit_error("minishell: ", "command not found "); // TODO: error message
	return (cmd);
}

static char	**get_env(char **ev)
{
	char	**array;

	array = NULL;
	while (*ev != NULL && ft_strncmp(*ev, "PATH=", 5) != 0)
		ev++;
	if (*ev == NULL)
		exit_error("minishell: ", "No such file or directory"); // TODO: error message
	if (ft_strncmp(*ev, "PATH=", 5) == 0)
	{
		array = ft_split(*ev + 5, ':');
		if (array == NULL)
			exit_error("minishell", "malloc failed "); // TODO: error message
	}
	return (array);
}

static char	*check_path(char *av, char **ev)
{
	char	**path_array;
	char	*tmp_path;
	char	*path;
	int		i;

	path_array = get_env(ev);
	i = -1;
	while (path_array[++i] != NULL)
	{
		tmp_path = ft_strjoin(path_array[i], "/");
		path = ft_strjoin(tmp_path, av);
		if (tmp_path != NULL)
			free(tmp_path);
		if (access(path, F_OK) == 0)
			break ;
		if (path != NULL)
			free(path);
		path = NULL;
	}
	i = -1;
	while (path_array[++i] != NULL)
		free(path_array[i]);
	free(path_array);
	return (path);
}

static char	*get_path(char **cmd, char **ev)
{
	char	*path;

	path = NULL;
	if (cmd[0][0] == '/')
	{
		path = ft_strdup(cmd[0]);
	}
	else
		path = check_path(cmd[0], ev);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", 2); // TODO: error message
		ft_putendl_fd(cmd[0], 2);
		while (*cmd != NULL)
			free(*cmd++);
		exit(127);
	}
	if (access(path, F_OK) == -1)
	{
		while (*cmd != NULL)
			free(*cmd++);
		free(cmd);
		exit_error("minishell: no such file or directory: ", path); // TODO: error message
	}
	return (path);
}

/*
The function execute_cmd is used to execute a command in a child process.
It takes as parameters the command to be executed and the environment.
It returns nothing.
*/

void	execute_cmd(char *av, char **env)
{
	char	**cmd;
	char	*path;

	cmd = get_cmd(av);
	path = get_path(cmd, env);
	if (execve(path, cmd, env) == -1)
	{
		// Error message management; execve failed
		exit (CMD_NOT_EXEC);
	}
}
