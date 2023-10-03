#include "../../includes/minishell.h"

// char **environment;

int	count_cmds(t_ast *root)
{
	t_ast	*tmp;
	int		counter;

	if (!root)
		return (0);
	if (root->type != AST_CMD)
		return (0);
	tmp = root;
	counter = 0;
	while (tmp)
	{
		counter++;
		tmp = tmp->right;
	}
	return (counter);
}

void	handle_normal_cmd(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(1); // TODO: Handle because there was an error, and exit
	if (pid == 0)
	{
		// setup redirections
		if (setup_redir(cmd, FALSE))
		{
			exit(EXIT_FAILURE);
		}
		execve(cmd->cmds[0], cmd->cmds, get()->env);
		// execute cmd
	}
	else
	{
		// If it's the last cmd, save its pid
	}
}

int	executor(void)
{
	t_ast	*root;

	root = get()->ast_tmp;
	execute_job(root);
	return (0);
}
