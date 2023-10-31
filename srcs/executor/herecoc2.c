#include "../../includes/minishell.h"

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

/* Execute the <and or> syntax block */
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

/* Execute the <cmd_line> syntax block */
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
