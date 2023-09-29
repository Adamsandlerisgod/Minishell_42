/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:44:00 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 17:20:12 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static char	**get_cmd(char *av)
{
	char	**cmd;

	if (av == NULL || ft_strlen(av) == 0)
	{
		error_cmd(av, "command not found");
		exit(CMD_NOT_FOUND);
	}
	cmd = ft_split(av, ' ');
	if (cmd == NULL)
	{
		error_system("malloc failed", errno);
		exit(CMD_NOT_EXEC);
	}
	if (cmd[0] == NULL)
	{
		error_cmd(av, "command not found");
		exit(CMD_NOT_FOUND);
	}
	return (cmd);
}

static char	**get_env(char **ev)
{
	char	**array;

	array = NULL;
	while (*ev != NULL && ft_strncmp(*ev, "PATH=", 5) != 0)
		ev++;
	if (*ev == NULL)
	{
		error_cmd("PATH", "No such file or directory");
		exit(CMD_NOT_FOUND);
	}
	if (ft_strncmp(*ev, "PATH=", 5) == 0)
	{
		array = ft_split(*ev + 5, ':');
		if (array == NULL)
		{
			error_system("malloc failed", errno);
			exit(CMD_NOT_EXEC);
		}
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
		error_cmd(cmd[0], "command not found");
		while (*cmd != NULL)
			free(*cmd++);
		exit(CMD_NOT_FOUND);
	}
	if (access(path, F_OK) == -1)
	{
		while (*cmd != NULL)
			free(*cmd++);
		free(cmd);
		error_cmd(path, "No such file or directory");
		exit(CMD_NOT_FOUND);
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
		error_system("execve failed\n", errno);
		exit (CMD_NOT_EXEC);
	}
}
