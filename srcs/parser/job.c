#include "minishell.h"

t_ast	*job(void)
{
	// t_ast	*job_node;

	get()->ast_root = command();
	return (get()->ast_root);
}

// <command> '|' <job>

t_ast	*j_case1(void)
{
	char	*pipe;

	if (!get()->ast_tmp->content)
	{
		if (get()->tokens_tmp->type == AST_PIPE)
		{
			pipe = ft_strdup(get()->tokens_tmp->content);
			get()->tokens_tmp = get()->tokens_tmp->next;
			get()->ast_tmp->content = pipe;
			job();
			return (get()->ast_tmp);
		}
	}
	return (NULL);
}

// // <command>

// t_ast	*j_case2(t_ast *job_node)
// {
	
// }