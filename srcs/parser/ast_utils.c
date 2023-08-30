#include "minishell.h"

t_ast	*ast_new_node(int type)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast));
	if (!new_node)
		return (NULL);
	new_node->right = NULL;
	new_node->left = NULL;
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
		if (parent->right)
		{
			tmp = parent->right;
			parent->right = child;
			child->right = tmp;
		}
		else
			parent->right = child;
		// child->left = NULL;
	}
	else
	{
		tmp = parent->left;
		parent->left = child;
		child->left = tmp;
		// child->right = NULL;
	}
}

void	*free_ast(t_ast	*head)
{
	if (!head)
		return (NULL);
	free_ast(head->left);
	free_ast(head->right);
	free (head->content);
	free (head);
	return (NULL);
}
