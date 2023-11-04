#include "../../includes/minishell.h"

void	free_tokens_ast()
{
	free_nodes();
	free_ast(get()->ast_tmp);
}
void	fptp()
{
	free_ptp(get()->env);
}

void	free_them_all()
{
	free_tokens_ast();
	fptp();
	free_builtins();
}