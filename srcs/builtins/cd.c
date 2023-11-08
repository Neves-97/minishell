/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:12:52 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:12:53 by ratavare         ###   ########.fr       */
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

int	ft_cd(char	**arg)
{
	char	*dir;
	char	*dir_tmp;
	int		i;

	dir_tmp = NULL;
	if (arg[0] && arg[1] && arg[2])
		return (1);
	i = search_env("HOME");
	if (!arg[1])
		dir = ft_strdup(get()->env[i] + 5);
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
