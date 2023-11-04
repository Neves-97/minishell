#include "../../includes/minishell.h"

int	execute_hd(t_ast *root)
{
	if (!hd_cmd_line(root))
		return (0);
	return (1);
}
