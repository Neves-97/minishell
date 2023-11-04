#include "../../includes/minishell.h"

static int	exec_builtin(t_cmd *cmd, t_built *builtin)
{
	if (setup_redir(cmd, TRUE))
	{
		free_tokens_ast();
		free_nodes();
		exit(EXIT_FAILURE);		// exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
	}
	// free(cmd->io);
	get()->exit_status = builtin->f(cmd->cmds);
	dup2(get()->fd[READ], STDIN_FILENO);
	dup2(get()->fd[WRITE], STDOUT_FILENO);
	return (1);
}

static int	exec_pipe_builtin(t_cmd *cmd, t_built *builtin)
{
	int	exit_code;

	if (setup_redir(cmd, TRUE))
		exit(EXIT_FAILURE);
	exit_code = builtin->f(cmd->cmds);
	dup2(get()->fd[READ], STDIN_FILENO);
	dup2(get()->fd[WRITE], STDOUT_FILENO);
	exit(exit_code);
}

t_built	*is_builtin_cmd(char *cmd)
{
	t_built	*builtin;

	builtin = get()->builtins;
	while (builtin)
	{
		if (!ft_strncmp(cmd, builtin->cmd, ft_strlen(builtin->cmd) + 1))
			return (builtin);
		builtin = builtin->next;
	}
	return (NULL);
}

static int	handle_normal_cmd(t_cmd *cmd, t_built *builtin)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_tokens_ast();
		free_nodes();
		exit(EXIT_FAILURE);		// exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
	}
	if (pid == 0)
	{
		// setup redirections
		child_signals();
		get()->child = TRUE;
		if (builtin)
		{
			exec_pipe_builtin(cmd, builtin);
		}
		if (setup_redir(cmd, FALSE))
		{
			exit(EXIT_FAILURE);
		}
		execute(cmd);
	}
	else
	{
		ignore_signals();
		if (!cmd->io->use_pipe[WRITE])
			get()->final_pid = pid;
		// If it's the last cmd, save its pid
	}
	return (1);
}

void	exec_cmd(t_cmd *cmd)
{
	t_built	*builtin;

	if (!cmd->cmds[0])
	{
		free_tokens_ast();
		free_nodes();
		exit(EXIT_FAILURE);		// exit(EXIT_FAILURE); // TODO: Handle because there was an error, and exit
	}
	builtin = is_builtin_cmd(cmd->cmds[0]);
	if (builtin && !cmd->io->use_pipe[READ] && !cmd->io->use_pipe[WRITE])
	{
		exec_builtin(cmd, builtin);
		return ;
	}
	handle_normal_cmd(cmd, builtin);
}
