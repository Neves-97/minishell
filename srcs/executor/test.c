#include "../../includes/minishell.h"

int	execute_ast(t_ast *root)
{
	exec_cmd_line(root);
	return (1);
}

int	execute_hd(t_ast *root)
{
	if (!hd_cmd_line(root))
		return (0);
	return (1);
}

void	execute_commands(t_ast *root)
{
	if (execute_hd(root))
		execute_ast(root);
}