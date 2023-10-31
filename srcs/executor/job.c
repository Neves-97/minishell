#include "../../includes/minishell.h"

void	execute_job(t_ast *root)
{
	int	pipe_fd[2];

	pipe_fd[READ] = -1;
	pipe_fd[WRITE] = -1;
	if (!root)
		return ;
	if (root->type == AST_PIPE)
		execute_pipe(root);
	else
		handle_command(root, setup_io(SINGLE_CMD, pipe_fd, 0));
	wait_exec();
}
