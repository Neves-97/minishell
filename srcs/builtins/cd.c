#include "minishell.h"

int	search_env(char *var)
{
	int	i;

	i = 0;
	while (get()->env[i] && ft_strncmp(get()->env[i], var, ft_strlen(var)))
		i++;
	return (i);
}

void	replace_pwd(void)
{
	char	cwd[PATH_MAX + 1];
	char	*new_pwd;

	getcwd(cwd, PATH_MAX + 1);
	ft_unset("PWD");
	new_pwd = ft_strjoin("PWD=", cwd);
	ft_export(new_pwd);
	free(new_pwd);
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
	if (chdir(dir) == -1)
		write(2, "cd: No such file or directory\n", 30);
	replace_pwd();
	free (dir);
	return (1);
}