/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:11 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:14:11 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	exec_builtin(t_cmd *cmd, t_built *builtin)
{
	if (setup_redir(cmd, TRUE))
		return (1);
	if (!ft_strncmp(cmd->cmds[0], "exit", 4) && \
	(!cmd->cmds[1] || !cmd->cmds[2]))
		free (cmd->io);
	get()->exit_status = builtin->f(cmd->cmds);
	dup2(get()->fd[READ], STDIN_FILENO);
	dup2(get()->fd[WRITE], STDOUT_FILENO);
	return (1);
}

static int	exec_pipe_builtin(t_cmd *cmd, t_built *builtin)
{
	int	exit_code;

	if (setup_redir(cmd, TRUE))
	{
		free_them_all();
		free_commands(cmd);
		exit(EXIT_FAILURE);
	}
	exit_code = builtin->f(cmd->cmds);
	dup2(get()->fd[READ], STDIN_FILENO);
	dup2(get()->fd[WRITE], STDOUT_FILENO);
	free_commands(cmd);
	free_them_all();
	exit(exit_code);
}

static void	child_process(t_cmd *cmd, t_built *builtin)
{
	child_signals();
	get()->child = TRUE;
	if (builtin)
		exec_pipe_builtin(cmd, builtin);
	if (setup_redir(cmd, FALSE))
	{
		free_them_all();
		free_commands(cmd);
		exit(EXIT_FAILURE);
	}
	execute(cmd);
}

static int	handle_normal_cmd(t_cmd *cmd, t_built *builtin)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_them_all();
		free_commands(cmd);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		child_process(cmd, builtin);
	else
	{
		ignore_signals();
		if (!cmd->io->use_pipe[WRITE])
			get()->final_pid = pid;
	}
	return (1);
}

void	exec_cmd(t_cmd *cmd)
{
	t_built	*builtin;

	if (!cmd->cmds[0])
	{
		free_them_all();
		free_commands(cmd);
		exit(EXIT_FAILURE);
	}
	builtin = is_builtin_cmd(cmd->cmds[0]);
	if (builtin && !cmd->io->use_pipe[READ] && !cmd->io->use_pipe[WRITE])
	{
		exec_builtin(cmd, builtin);
		return ;
	}
	handle_normal_cmd(cmd, builtin);
}
