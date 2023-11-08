/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:30 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:13:31 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*valid_path(t_cmd *cmd)
{
	char	*full_path;
	char	*env_path;

	if (cmd->cmds[0][0] == '/' || !ft_strncmp(cmd->cmds[0], "./", 2)
		|| !ft_strncmp(cmd->cmds[0], "../", 3))
	{
		if (!is_directory2(cmd->cmds[0], cmd))
			full_path = ft_strdup(cmd->cmds[0]);
	}
	else if (!ft_strncmp(cmd->cmds[0], "~/", 2))
		full_path = sub_tild_dir(cmd->cmds[0]);
	else
	{
		env_path = get_env_value("PATH=");
		if (env_path[0] == '\0')
		{
			ft_putstr_fd(cmd->cmds[0], STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			free_them_all();
			free_commands(cmd);
			exit(127);
		}
		full_path = search_path(cmd->cmds[0], env_path);
	}
	return (full_path);
}

void	exec_error(t_cmd *cmd, char *full_path)
{
	(void) full_path;
	free_commands(cmd);
	free_them_all();
	exit(127);
}

void	execv_cmd(char *full_path, t_cmd *cmd)
{
	execve(full_path, cmd->cmds, get()->env);
	perror(full_path);
	exit(check_error(full_path, cmd));
}

void	execute(t_cmd *cmd)
{
	char	*full_path;

	full_path = valid_path(cmd);
	if (full_path != NULL)
		execv_cmd(full_path, cmd);
	else
		exec_error(cmd, full_path);
}
