#include "minishell.h"

t_ast	*ast_new_node(int type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->content = NULL;
	new_node->type = type;
	return (new_node);
}

void	ast_add_node(t_ast	*parent, t_ast	*child, int right)
{
	t_ast	*tmp;

	if (!parent || !child)
		return ;
	if (right)
	{
		tmp = parent->right;
		parent->right = child;
		child->right = tmp;
		child->left = NULL;
	}
	else
	{
		tmp = parent->left;
		parent->left = child;
		child->left = tmp;
		child->right = NULL;
	}
}
