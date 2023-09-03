#include "minishell.h"

t_ast	*job(void)
{
	t_ast	*new_node;
	t_list	*backup;

	backup = get()->tokens_tmp;
	new_node = j_case1();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = j_case2();
	if (new_node)
		return (new_node);
	return (NULL);
}

// <command> '|' <job>

t_ast	*j_case1(void)
{
	t_ast	*new_node;
	t_ast	*cmd_node;
	t_ast	*job_node;

	cmd_node = command();
	if (!cmd_node)
		return (NULL);
	if (!get()->tokens_tmp || get()->tokens_tmp->type != AST_PIPE 
		|| !get()->tokens_tmp->next)
		return (free_ast(cmd_node));
	new_node = ast_new_node(AST_PIPE);
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(get()->tokens_tmp->content);
	ast_add_node(new_node, get()->ast_tmp, 0);
	get()->ast_tmp = new_node;
	get()->tokens_tmp = get()->tokens_tmp->next;
	job_node = job();
	if (!job_node)
		return (free_ast(new_node));
	ast_add_node(new_node, job_node, 1);
	return (new_node);
}

// // <command>

t_ast	*j_case2(void)
{
	t_ast	*new_node;

	if (!get()->tokens_tmp || get()->tokens_tmp->type != AST_CMD)
		return (NULL);
	new_node = command();
	if (!new_node)
		return (NULL);
	if ((get()->tokens_tmp && !(get()->tokens_tmp->next)))
		return (free_ast(new_node));
	return (new_node);
}
