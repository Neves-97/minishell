/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:12:52 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 17:05:22 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	search_env(char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (get()->env[i])
	{
		while (get()->env[i][j] != '=')
			j++;
		if (!(strncmp(get()->env[i], var, j)) && j == ((int)ft_strlen(var)))
			break ;
		j = 0;
		i++;
	}
	return (i);
}

void	replace_pwd(void)
{
	char	cwd[PATH_MAX + 1];
	char	*new_pwd;

	getcwd(cwd, PATH_MAX + 1);
	ft_unset_arg("PWD");
	new_pwd = ft_strjoin("PWD=", cwd);
	ft_export_arg(new_pwd);
	free(new_pwd);
}

int	cd_err(char *dir)
{
	free (dir);
	write(2, "cd: No such file or directory\n", 30);
	return (1);
}

int	get_home(char **dir)
{
	int	i;

	i = search_env("HOME");
	if (!get()->env[i])
	{
		ft_putendl_fd("cd: HOME not set", 2);
		return (0);
	}
	dir[0] = ft_strdup(get()->env[i] + 5);
	if (!dir[0])
	{
		free (dir[0]);
		return (0);
	}
	return (1);
}

int	ft_cd(char	**arg)
{
	static char		*dir;
	static char		*dir_tmp;

	if (arg[1] && arg[2])
		return (1);
	if (!arg[1])
	{
		if (!get_home(&dir))
			return (1);
	}
	else if (arg[1][0] == '/')
		dir = ft_strdup(arg[1]);
	else
	{
		dir = getcwd(NULL, PATH_MAX + 1);
		dir_tmp = ft_strjoin(dir, "/");
		free (dir);
		dir = ft_strjoin(dir_tmp, arg[1]);
		free (dir_tmp);
	}
	if (chdir(dir) == -1)
		return (cd_err(dir));
	replace_pwd();
	free (dir);
	return (0);
}
