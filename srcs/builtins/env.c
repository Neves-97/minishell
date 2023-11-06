#include "../../includes/minishell.h"

int	ft_env(char **args)
{
	int		i;
	char	*str;

	i = 0;
	if (args[0] && args[1])
	{
		str = ft_strdup(args[1]);
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		free (str);
		return (127);
	}
	if (!get()->env || !get()->env[0])
		return (0);
	while (get()->env[i])
		ft_printf("%s\n", get()->env[i++]);
	return (0);
}
