#include "../../includes/minishell.h"

void	free_tokens_ast()
{
	free_nodes();
	free_ast(get()->ast_tmp);
}
