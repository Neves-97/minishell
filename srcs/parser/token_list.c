#include "minishell.h"


// redir block missing

t_ast	*token_list(void)
{
	t_list	*backup;
	t_ast	*new_node;

	if (!get()->tokens_tmp)
		return (NULL);
	if (!get()->ast_tmp)
		return (NULL);
	backup = get()->tokens_tmp;
	new_node = tl_case1();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = tl_case2();
	// if (new_node)
	// 	return (new_node);
	return (NULL);
}

// [name]  <token list>

t_ast	*tl_case1(void)
{
	char	*cmd;

	if (!get()->ast_tmp->content)
	{
		// check if the current lexer token is arg
		if (get()->tokens_tmp->type == 0)
		{
			cmd = ft_strdup(get()->tokens_tmp->content);
			get()->tokens_tmp = get()->tokens_tmp->next;
			get()->ast_tmp->content = cmd;
			token_list();
			return (get()->ast_tmp);
		}
	}
	return (NULL);
}

// [token] <token list>

t_ast	*tl_case2(void)
{
	char	*arg;
	t_ast	*node;

	if (!get()->tokens_tmp->type == 0)
		return (NULL);
	node = ast_new_node(AST_ARG);
	arg = ft_strdup(get()->tokens_tmp->content);
	if (!arg)
		return (NULL);
	get()->tokens_tmp = get()->tokens_tmp->next;
	node->content = arg;
	token_list();
	ast_add_node(get()->ast_tmp, node, 1);
	return (node);
}


