/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_cd_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:02:14 by jhurpy            #+#    #+#             */
/*   Updated: 2023/09/09 17:38:09 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/execute.h"

/*
The function set_oldpwd() is used to set the previous working directory.
*/

static void	set_oldpwd(char **ev)
{
	char	*oldpwd;
	char	*tmp;
	int		i;

	oldpwd = getcwd(NULL, 0);
	tmp = ft_strjoin("OLDPWD=", oldpwd);
	i = 0;
	while (ft_strncmp(ev[i], "OLDPWD", 6) != 0)
		i++;
	free(ev[i]);
	ev[i] = tmp;
	free(oldpwd);
}

/*
The function set_pwd() is used to set the current working directory.
*/

static void	set_pwd(char **ev)
{
	char	*pwd;
	char	*tmp;
	int		i;

	pwd = getcwd(NULL, 0);
	tmp = ft_strjoin("PWD=", pwd);
	i = 0;
	while (ft_strncmp(ev[i], "PWD=", 4) != 0)
		i++;
	free(ev[i]);
	ev[i] = tmp;
	free(pwd);
}

/*
The function check_path() is used to check if the path is valid.
If the path is not valid, the function returns false.
*/

static bool	check_path(t_cmd *cmd, int i)
{
	struct stat	*buf;

	if (ft_strlen(cmd[i].cmd[1]) == 0 || ft_strlen(cmd[i].cmd[1]) >= 1024 ||
		cmd[i].cmd[1] == NULL || ft_strncmp(cmd[i].cmd[1], "~", 2) == 0 ||
		ft_strncmp(cmd[i].cmd[1], "/", 2) == 0)
		{
			msg_cmd("minishell: cd:", cmd[i].cmd[1], "invalid path", 2);
			return (false);
		}
	buf = (struct stat *)malloc(sizeof(struct stat));
	if (stat(cmd[i].cmd[1], buf) == -1)
	{
		msg_cmd("minishell: cd:", cmd[i].cmd[1], "No such file or directory", 2);
		free(buf);
		return (false);
	}
	if (!S_ISDIR(buf->st_mode))
	{
		msg_cmd("minishell: cd:", cmd[i].cmd[1], "Not a directory", 2);
		free(buf);
		return (false);
	}
	free(buf);
	return (true);
}

/*
The function cd_builtins() is used to change the current working directory.
If the path is not valid, the function returns 1.
*/

int	cd_builtins(t_cmd *cmd, char **ev, int i)
{
	if (cmd[i].cmd[1][0] == '-')
	{
		msg_cmd("minishell: cd:", cmd[i].cmd[1],
			": option not accepted", 2);
		msg_cmd("cd: usage: cd [directory]", NULL, NULL, 2);
		return (1);
	}
	if (check_path(cmd, i) == false)
		return (1);
	set_oldpwd(ev);
	chdir(cmd->cmd[1]);
	set_pwd(ev);
	return (0);
}
