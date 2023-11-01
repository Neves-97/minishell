#include "minishell.h"

void	print_ast(t_ast *root, int spaces)
{
	if (!root)
		return ;
	if (root->right)
		print_ast(root->right, spaces + 5);
	for (int i = 0; i < spaces; i++)
		printf(" ");
	if (root->content)
		printf("%s\n", root->content);
	if (root->left)
		print_ast(root->left, spaces + 5);
}

void	free_builtins(void)
{
	t_built	*tmp;

	while (get()->builtins)
	{
		tmp = get()->builtins->next;
		if (get()->builtins)
			free (get()->builtins);
		get()->builtins = tmp;
	}
}