/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:40 by jhurpy            #+#    #+#             */
/*   Updated: 2023/12/02 19:01:09 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_oldpwd(t_env *env, char *oldpwd)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, "OLDPWD=", 7) == 0)
		{
			free(tmp_env->name);
			tmp_env->name = ft_strdup(oldpwd);
			break ;
		}
		else if (tmp_env->next == NULL)
		{
			add_variable(tmp_env, oldpwd);
			break ;	
		}
		tmp_env = tmp_env->next;
	}
}

static void	set_variable_pwd(t_env *env)
{
	t_env	*tmp_env;
	char	*tmp_pwd;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, "PWD=", 4) == 0)
		{
			tmp_pwd = ft_strjoin("OLDPWD=", tmp_env->name + 4);
			free(tmp_env->name);
			tmp_env->name = ft_strjoin("PWD=", getcwd(NULL, 0));
		}
		tmp_env = tmp_env->next;
	}
	set_oldpwd(env, tmp_pwd);
}

// static bool	check_path(t_cmd *cmd, int i)
// {
// 	struct stat	*buf;
	
// 	if (ft_strlen(cmd[i].cmd[1]) == 0 || ft_strlen(cmd[i].cmd[1]) >= PATH_MAX
// 		|| cmd[i].cmd[1] == NULL || ft_strncmp(cmd[i].cmd[1], "~", 2) == 0
// 		|| ft_strncmp(cmd[i].cmd[1], "/", 2) == 0)
// 	{
// 		error_cmd(cmd[i].cmd[0], "invalid path.");
// 		return (false);
// 	}
// 	buf = (struct stat *)malloc(sizeof(struct stat));
// 	if (stat(cmd[i].cmd[1], buf) == -1)
// 	{
// 		error_cmd(cmd[i].cmd[0], "no such file or directory.");
// 		free(buf);
// 		return (false);
// 	}
// 	if (!S_ISDIR(buf->st_mode))
// 	{
// 		error_cmd(cmd[i].cmd[0], "not a directory.");
// 		free(buf);
// 		return (false);
// 	}
// 	free(buf);
// 	return (true);
// }

/*
The function cd_builtins is used to change the current working directory
to the directory specified in the path and update the environment.
If the path is not valid, the function returns 1.
If the path is valid, the function returns 0.
*/

/*
Find a way to manage "~", "/" and no argument as absolut or relative path.
Creat function and implemetation
*/

static int	change_directory(char *path, t_env *env)
{
	if (chdir(path) == -1)
	{
		error_system("chdir failed");
		return (CMD_ERROR);
	}
	set_variable_pwd(env);
	return (CMD_OK);
}

int	ft_cd(t_data *data, int index)
{
	char	*path;

// 	if (!data->cmd[index].cmd || ft_isspace(data->cmd[index].cmd[1][0])
// 		|| data->cmd[index].cmd[1][0] == '\0'
// 		|| ft_strncmp(data->cmd[index].cmd[1], "--", 3))
// 	{
// 		path = get_env_value("HOME", data->env, 4);// function to get the variable "HOME"
// 		if (!path || *path == '\0' || ft_isspace(*path))
// 			return (error_cmd(data->cmd[index].cmd[0], "HOME not set"), CMD_EXIT);
// 		return (!change_dir(data, path));
// 	}
// 	if (data->cmd[index].cmd[2])
// 		return (error_cmd(data->cmd[index].cmd[0], "too many arguments"), CMD_EXIT);
// 	if (ft_strncmp(data->cmd[index].cmd, "-", 2) == 0)
// 	{
// 		path = get_env_value("OLDPATH", data->env, 7); // function to get the variable "OLDPATH"
// 		if (!path)
// 			return (error_cmd(data->cmd[index].cmd[0], "OLDPWD not set"), CMD_EXIT);
// 		return (/*function to change the directory*/0);
// 	}
// 	return (/*function to change directory*/0);
// }

	printf("IN BUITLINS\n");
	path = NULL;
	if (!data->cmd[index].cmd || !data->cmd[index].cmd[1]
		|| ft_isspace(data->cmd[index].cmd[1][0])
		|| data->cmd[index].cmd[1][0] == '\0'
		|| ft_strncmp(data->cmd[index].cmd[1], "--", 3) == 0)
	{
		path = get_env_value("HOME", &data->env, 4);
		return (!change_directory(path, data->env));
	}
	if (data->cmd[index].cmd[2])
		return (error_cmd(data->cmd[index].cmd[0], "too many arguments"), CMD_EXIT);
	// if (data->cmd[index].cmd[1] == NULL)
	// 	return (error_cmd(data->cmd[index].cmd[0], "missed a option."), CMD_EXIT);
	// if (data->cmd[index].cmd[1][0] == '-')
	// {
	// 	error_cmd(data->cmd[index].cmd[0], "no option accepted.");
	// 	return (CMD_EXIT);
		// }
	if (ft_strncmp(data->cmd[index].cmd[0], "-", 2) == 0)
	{
		path = get_env_value("OLDPWD", &data->env, 7); // function to get the variable "OLDPATH"
		if (!path)
			return (error_cmd(data->cmd[index].cmd[0], "OLDPWD not set"), CMD_EXIT);
		return (!change_directory(path, data->env));
	}
	// if (check_path(data->cmd, index) == false)
	// 	return (CMD_EXIT);
	// if (chdir(data->cmd[index].cmd[1]) == -1)
	// {
	// 	error_system("chdir failed");
	// 	return (CMD_ERROR);
	// }
	// set_variable_pwd(data->env);
	path = data->cmd[index].cmd[1];
	return (!change_directory(path, data->env));


}
