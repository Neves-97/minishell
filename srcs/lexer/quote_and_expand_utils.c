#include "minishell.h"

int	is_any_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}
