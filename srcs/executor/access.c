/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:26 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 16:20:21 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*sub_tild_dir(char *relative)
{
	char	*full;
	char	*home;

	home = get_env_value("HOME=");
	full = ft_strjoin(home, &relative[1]);
	return (full);
}

char	*search_path(char *cmd, char *env_path)
{
	char	**env;
	char	*path;
	char	*temp;
	int		i;

	env = ft_split(env_path, ':');
	i = 0;
	while (env[i])
	{
		temp = ft_strjoin(env[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK) == 0)
		{
			free_split(env);
			return (path);
		}
		free(path);
		i++;
	}
	free_split(env);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": Command not found\n", STDERR_FILENO);
	return (NULL);
}

int	is_directory(char *cmd)
{
	static struct stat	s;

	if (lstat(cmd, &s) && \
		ft_strncmp("./", cmd, 2 && cmd[0] != '/'))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (S_ISDIR(s.st_mode) && (cmd[0] == '/' || \
		!ft_strncmp("./", cmd, 2)) && !access(cmd, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		free_them_all();
		exit(126);
	}
	return (0);
}

int	is_directory2(char *cmd, t_cmd *cmds)
{
	static struct stat	s;

	if (lstat(cmd, &s) && \
		ft_strncmp("./", cmd, 2 && cmd[0] != '/'))
	{
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	if (S_ISDIR(s.st_mode) && (cmd[0] == '/' || \
		!ft_strncmp("./", cmd, 2)) && !access(cmd, F_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putendl_fd(": Is a directory", 2);
		free_them_all();
		free_commands(cmds);
		exit(126);
	}
	return (0);
}

int	check_error(char *path, t_cmd *cmd)
{
	if (access(path, X_OK))
	{
		get()->exit_status = 126;
		free_them_all();
		free (path);
		free_commands(cmd);
		return (127);
	}
	return (EXIT_FAILURE);
}
