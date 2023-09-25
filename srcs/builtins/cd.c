#include "minishell.h"

int	search_env(char *var)
{
	int	i;

	i = 0;
	while (get()->env[i] && ft_strncmp(get()->env[i], var, ft_strlen(var)))
		i++;
	return (i);
}

int	ft_cd(char	*arg)
{
	char	*dir;
	char	*dir_tmp;
	int		i;

	dir_tmp = NULL;
	i = search_env("HOME");
	if (!arg || !arg[0])
		dir = ft_strdup(get()->env[i] + 5);
	else if (arg[0] == '/')
		dir = ft_strdup(arg);
	else
	{
		dir = getcwd(NULL, PATH_MAX + 1);
		dir_tmp = ft_strjoin(dir, "/");
		free (dir);
		dir = ft_strjoin(dir_tmp, arg);
		free (dir_tmp);
	}
	ft_printf("%s\n", dir);
	free (dir);
	return (1);
}
