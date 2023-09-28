#include "minishell.h"

int	ft_exit(void)
{
	write(1, "\nexit\n", 6);
	free_ptp(get()->env);
	free_ptp(get()->export);
	free_nodes();
	free_ast(get()->ast_tmp);
	return (0);
}
