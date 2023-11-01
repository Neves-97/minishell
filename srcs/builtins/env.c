#include "../../includes/minishell.h"

int	ft_env(char **args)
{
	int	i;

	i = 0;
	(void)args;
	if (!get()->env || !get()->env[0])
		return (0);
	while (get()->env[i])
		ft_printf("%s\n", get()->env[i++]);
	return (0);
}
