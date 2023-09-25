#include "minishell.h"

void	parser(void)
{
	get()->tokens_tmp = get()->tokens;
	get()->ast_tmp = and_or();
}
