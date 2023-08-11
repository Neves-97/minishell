#include "minishell.h"

t_ast	*command(void)
{
	t_ast	*cmd_node;

	cmd_node = ast_new_node(AST_CMD);
	if (!cmd_node)
		return (NULL);
	cmd_node->left = NULL;
	cmd_node->right = NULL;
	get()->ast_tmp = cmd_node;
	token_list();
	return (NULL);
}
