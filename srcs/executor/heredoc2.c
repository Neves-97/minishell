#include "../../includes/minishell.h"

int	hd_pipe(t_ast *root)
{
	t_ast	*job;

	if (!hd_command(root->left))
		return (0);
	job = root->right;
	while (job && job->type == AST_PIPE)
	{
		if (!hd_command(job->left))
			return (0);
		job = job->right;
	}
	if (!hd_command(job))
		return (0);
	return (1);
}

/* Execute the <job> syntax block */
int	hd_job(t_ast *root)
{
	if (!root)
		return (1);
	if (root->type == AST_PIPE)
	{
		if (!hd_pipe(root))
			return (0);
	}
	else
	{
		if (!hd_command(root))
			return (0);
	}
	return (1);
}

// /* Execute the <and or> syntax block */
int	hd_and_or(t_ast *root)
{
	if (!root)
		return (1);
	if (root->type == AST_AND || root->type == AST_OR || root->type == 1)
	{
		if (!hd_and_or(root->left))
			return (0);
		if (!hd_and_or(root->right))
			return (0);
	}
	else
	{
		if (!hd_job(root))
			return (0);
	}
	return (1);
}

// /* Execute the <cmd_line> syntax block */
int	hd_cmd_line(t_ast *root)
{
	if (!root)
		return (1);
	if (root->type == 1)
	{
		if (!hd_and_or(root->left))
			return (0);
		if (!hd_and_or(root->right))
			return (0);
	}
	else
	{
		if (!hd_and_or(root))
			return (0);
	}
	return (1);
}

int	execute_hd(t_ast *root)
{
	if (!hd_cmd_line(root))
		return (0);
	return (1);
}
