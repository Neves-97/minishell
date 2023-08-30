#include "minishell.h"

t_ast	*command(void)
{
	t_ast	*cmd_node;

	cmd_node = ast_new_node(AST_CMD);
	if (!cmd_node)
		return (NULL);
	get()->ast_tmp = cmd_node;
	if (!token_list())
	{
		free_ast(cmd_node);
		return (NULL);
	}
	return (cmd_node);
}
