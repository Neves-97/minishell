#include "minishell.h"

t_ast	*redir_in(void)
{
	t_ast	*new_node;
	t_list	*backup;

	backup = get()->tokens_tmp;
	new_node = redir_in_case1();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = redir_in_case2();
	if (new_node)
		return (new_node);
	return (NULL);
}

// "<<" [file]

t_ast	*redir_in_case1(void)
{
	t_ast	*new_node;

	if (!get()->tokens_tmp || !get()->tokens_tmp->next)
		return (NULL);
	if (get()->tokens_tmp->type != AST_IN || \
		get()->tokens_tmp->next->type != AST_IN)
		return (NULL);
	get()->tokens_tmp = get()->tokens_tmp->next->next;
	if (!get()->tokens_tmp)
		return (NULL);
	new_node = ast_new_node(AST_RDI_HD);
	new_node->content = ft_strdup(get()->tokens_tmp->content);
	get()->tokens_tmp = get()->tokens_tmp->next;
	return (new_node);
}

// "<" [file]

t_ast	*redir_in_case2(void)
{
	t_ast	*new_node;

	if (!get()->tokens_tmp)
		return (NULL);
	if (get()->tokens_tmp->type != AST_IN)
		return (NULL);
	get()->tokens_tmp = get()->tokens_tmp->next;
	if (!get()->tokens_tmp || (!get()->tokens_tmp->type) == 0)
		return (NULL);
	new_node = ast_new_node(AST_RDI);
	new_node->content = ft_strdup(get()->tokens_tmp->content);
	get()->tokens_tmp = get()->tokens_tmp->next;
	return (new_node);
}
