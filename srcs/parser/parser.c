#include "minishell.h"

void	parser(void)
{
	get()->tokens_tmp = get()->tokens;
	job();
}
