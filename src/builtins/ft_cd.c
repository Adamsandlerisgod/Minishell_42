/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:40 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/29 01:34:38 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static void	set_oldpwd(t_env *env, char *oldpwd)
{
	t_env	*tmp_env;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, "OLDPWD=", 7) == 0)
		{
			free(tmp_env->name);
			tmp_env->name = oldpwd;
		}
		tmp_env = tmp_env->next;
	}
	if (!tmp_env)
	{
		tmp_env = (t_env *)malloc(sizeof(t_env));
		if (tmp_env == NULL)
			error_system("malloc failed\n", errno);
		tmp_env->name = oldpwd;
		tmp_env->next = NULL;
	}
}

static void	set_env(t_env *env)
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

static bool	check_path(t_cmd *cmd, int i)
{
	struct stat	*buf;

	if (ft_strlen(cmd[i].cmd[1]) == 0 || ft_strlen(cmd[i].cmd[1]) >= PATH_MAX
		|| cmd[i].cmd[1] == NULL || ft_strncmp(cmd[i].cmd[1], "~", 2) == 0
		|| ft_strncmp(cmd[i].cmd[1], "/", 2) == 0)
	{
		error_cmd(cmd[i].cmd[0], "invalid path.");
		return (false);
	}
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (stat(cmd[i].cmd[1], buf) == -1)
	{
		error_cmd(cmd[i].cmd[0], "no such file or directory.");
		free(buf);
		return (false);
	}
	if (!S_ISDIR(buf->st_mode))
	{
		error_cmd(cmd[i].cmd[0], "not a directory.");
		free(buf);
		return (false);
	}
	free(buf);
	return (true);
}

/*
The function cd_builtins is used to change the current working directory
to the directory specified in the path and update the environment.
If the path is not valid, the function returns 1.
If the path is valid, the function returns 0.
*/

int	ft_cd(t_data *data, int index)
{
	if (data->cmd[index].cmd[1][0] == '-')
	{
		error_cmd(data->cmd[index].cmd[0], "no option accepted.");
		return (CMD_EXIT);
	}
	if (check_path(data->cmd, index) == false)
		return (CMD_EXIT);
	if (chdir(data->cmd[index].cmd[1]) == -1)
	{
		error_system("chdir failed\n", errno);
		return (CMD_ERROR);
	}
	set_env(data->env);
	return (CMD_OK);
}
