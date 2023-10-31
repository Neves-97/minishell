#include "../../includes/minishell.h"

int	export_check(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '=')
		return (0);
	while (arg[i])
	{
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(char *arg)
{
	int		i;
	char	**new_env;

	if (!export_check(arg))
		return (0);
	i = 0;
	while (get()->env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (get()->env[i])
	{
		new_env[i] = ft_strdup(get()->env[i]);
		i++;
	}
	new_env[i] = ft_strdup(arg);
	free_ptp(get()->env);
	get()->env = new_env;
	return (1);
}
