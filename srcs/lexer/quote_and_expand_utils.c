#include "minishell.h"

int	is_qt(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
