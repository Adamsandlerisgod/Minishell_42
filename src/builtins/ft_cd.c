/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:15:40 by jhurpy            #+#    #+#             */
/*   Updated: 2024/01/24 13:10:30 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
The function ft_cd is used to change the current working directory
to the directory specified in the path and update the environment.
*/

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
	free(oldpwd);
}

static void	set_variable_pwd(t_env *env)
{
	t_env	*tmp_env;
	char	*tmp_pwd;
	char	*cwd;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->name, "PWD=", 4) == 0)
		{
			tmp_pwd = ft_strjoin("OLDPWD=", tmp_env->name + 4);
			free(tmp_env->name);
			cwd = getcwd(NULL, 0);
			tmp_env->name = ft_strjoin("PWD=", cwd);
			free(cwd);
		}
		tmp_env = tmp_env->next;
	}
	set_oldpwd(env, tmp_pwd);
}

static void	change_directory(char *path, t_env *env, bool flag)
{
	g_exit_status = CMD_OK;
	if (flag == true)
	{
		if (ft_strlen(path) > 0)
			printf("%s\n", path);
		else
			printf("%scd: OLDPWD not set\n", PROMPT_R);
	}
	if (chdir(path) == -1)
	{
		error_cmd_msg("cd ", path, NO_FILE);
		g_exit_status = CMD_ERROR;
	}
	set_variable_pwd(env);
	if (path != NULL)
		free(path);
}

static char	*change_home_oldpwd(t_data *data, int index)
{
	char	*var;

	var = NULL;
	if (!data->cmd[index].cmd || !data->cmd[index].cmd[1]
		|| ft_isspace(data->cmd[index].cmd[1][0])
		|| data->cmd[index].cmd[1][0] == '\0'
		|| ft_strncmp(data->cmd[index].cmd[1], "--", 3) == 0)
		var = ft_strdup("HOME");
	else if (ft_strncmp(data->cmd[index].cmd[1], "-", 2) == 0)
		var = ft_strdup("OLDPWD");
	return (var);
}

void	ft_cd(t_data *data, int index)
{
	char	*path;
	char	*var;
	bool	flag;

	path = NULL;
	flag = false;
	var = change_home_oldpwd(data, index);
	if (var != NULL)
	{
		if (ft_strncmp("OLDPWD", var, 7) == 0)
			flag = true;
	}
	if (var != NULL)
		path = get_home_oldpwd_path(var, data);
	else if (path == NULL && flag == false)
		path = ft_strdup(data->cmd[index].cmd[1]);
	change_directory(path, data->env, flag);
}
