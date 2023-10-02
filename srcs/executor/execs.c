#include "../../includes/minishell.h"

void	execute_job(t_ast *root)
{
	int	pipe_fd[2];

	pipe_fd[READ] = -1;
	pipe_fd[WRITE] = -1;
	if (!root)
		return ;
	if (root->type == AST_PIPE)
		execute_pipe(root); //TODO: Call execute_pipe function
	else
		handle_command(root, setup_io(SINGLE_CMD, pipe_fd, 0));
	wait_exec();
}

void	exec_ast(t_ast *root)
{
	if (root == NULL)
		return ;
	if (root->type == AST_CMD)
		printf("command: %s\n", root->content);
	else if (root->type == AST_ARG)
		printf("arg: %s\n", root->content);
	else if (root->type == AST_RDI)
		printf("redirect in: %s\n", root->content);
	else if (root->type == AST_RDO_AP)
		printf("redirect apend: %s\n", root->content);
	else if (root->type == AST_RDO_TR)
		printf("redirect subs: %s\n", root->content);
	else if (root->type == AST_RDI_HD)
		printf("redirect heredoc: %s\n", root->content);
	exec_ast(root->left);
	exec_ast(root->right);
}

void	exec_cmd(t_cmd *cmd)
{
	if (!cmd->cmds)
		exit(1); // TODO: Handle because there was an error, and exit
	handle_normal_cmd(cmd);
}
