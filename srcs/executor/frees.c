#include "../../includes/minishell.h"

void	free_tokens_ast(void)
{
	free_nodes();
	free_ast(get()->ast_tmp);
}

void	free_them_all(void)
{
	free_tokens_ast();
	free_ptp(get()->env);
	free_builtins();
}
