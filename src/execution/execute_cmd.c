/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:44:00 by jhurpy            #+#    #+#             */
/*   Updated: 2023/10/09 12:54:33 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static bool	check_cmd_accessible(char **cmd)
{
	if (ft_strncmp(cmd[0], "../", 3) == 0 || ft_strncmp(cmd[0], "./", 3) == 0)
	{
		if (access(cmd[0], F_OK) == -1)
		{
			error_cmd(cmd[0], "No such file or directory");
			exit(CMD_NOT_FOUND);
		}
		if (access(cmd[0], X_OK) == -1)
		{
			error_cmd(cmd[0], "Permission denied");
			exit(CMD_NOT_EXEC);
		}
	}
	return (true)
}

static char	**get_env(char **env)
{
	char	**array;

	array = NULL;
	while (*env != NULL && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
	{
		error_cmd("PATH", "No such file or directory");
		exit(CMD_NOT_FOUND);
	}
	if (ft_strncmp(*env, "PATH=", 5) == 0)
	{
		array = ft_split(*env + 5, ':');
		if (array == NULL)
		{
			error_system("malloc failed", errno);
			exit(CMD_NOT_EXEC);
		}
	}
	return (array);
}

static char	*check_path(char *av, char **env)
{
	char	**path_array;
	char	*tmp_path;
	char	*path;
	int		i;

	path_array = get_env(env);
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

static char	*get_path(char **cmd, char **env)
{
	char	*path;

	path = NULL;
	if (cmd[0][0] == '/')
	{
		path = ft_strdup(cmd[0]);
	}
	else
		path = check_path(cmd[0], env);
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

void	execute_cmd(char **cmd, char **env)
{
	char	*path;

	if (cmd == NULL || cmd[0] == NULL)
		exit(CMD_NOT_FOUND);
	if (check_cmd_accessible(cmd) == true)
		path = cmd[0];
	else
		path = get_path(cmd, env);
	if (execve(path, cmd, env) == -1)
	{
		error_system("execve failed\n", errno);
		exit (CMD_ERROR);
	}
}
