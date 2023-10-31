#include "../../includes/minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !env[0])
		return (0);
	while (env[i])
		ft_printf("%s\n", env[i++]);
	return (1);
}

