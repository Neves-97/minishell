#include "../../includes/minishell.h"

void	exec_and_or(t_ast *root)
{
	if (!root)
		return ;
	if (root->type == AST_AND)
	{
		exec_and_or(root->left);
		if (get()->exit_status == 0)
			exec_and_or(root->right);
	}
	else if (root->type == AST_OR)
	{
		exec_and_or(root->left);
		if (get()->exit_status != 0)
			exec_and_or(root->right);
	}
	else
		execute_job(root);
}

void	exec_cmd_line(t_ast *root)
{
	if (!root)
		return ;
	if (root->type == 1)
	{
		exec_and_or(root->left);
		exec_cmd_line(root->right);
	}
	else
		exec_and_or(root);
}
