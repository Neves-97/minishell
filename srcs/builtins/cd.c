#include "../../includes/minishell.h"

int	search_env(char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (get()->env[i])
	{
		while (get()->env[i][j] != '=')
			j++;
		if (!(ft_strncmp(get()->env[i], var, j)))
			break ;
		j = 0;
		i++;
	}
	return (i);
}

// void	replace_pwd(void)
// {
// 	char	cwd[PATH_MAX + 1];
// 	char	*new_pwd;

// 	getcwd(cwd, PATH_MAX + 1);
// 	ft_unset("PWD");
// 	new_pwd = ft_strjoin("PWD=", cwd);
// 	ft_export(new_pwd);
// 	free(new_pwd);
// }

// int	ft_cd(char	*arg)
// {
// 	char	*dir;
// 	char	*dir_tmp;
// 	int		i;

// 	dir_tmp = NULL;
// 	i = search_env("HOME");
// 	if (!arg || !arg[0])
// 		dir = ft_strdup(get()->env[i] + 5);
// 	else if (arg[0] == '/')
// 		dir = ft_strdup(arg);
// 	else
// 	{
// 		dir = getcwd(NULL, PATH_MAX + 1);
// 		dir_tmp = ft_strjoin(dir, "/");
// 		free (dir);
// 		dir = ft_strjoin(dir_tmp, arg);
// 		free (dir_tmp);
// 	}
// 	if (chdir(dir) == -1)
// 		write(2, "cd: No such file or directory\n", 30);
// 	replace_pwd();
// 	free (dir);
// 	return (1);
// }



// t_list	*ft_listilia(char *value)
// {
// 	t_list	*new;

// 	new = (t_list *)malloc(sizeof(t_list));
// 	if (!new)
// 		return (NULL);
// 	new->content = value;
// 	new->next = NULL;
// 	return (new);
// }

// /* Frees NEW_PATH and CWD, if not NULL */
// void	free_paths(char *new_path, char *cwd)
// {
// 	if (new_path)
// 		free(new_path);
// 	if (cwd)
// 		free(cwd);
// }

// /* Check if arguments are correct and print error message accordingly */
// int	incorrect_args(char **path)
// {
// 	if (!path[1] || (path[1] && !path[2]))
// 		return (0);
// 	ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
// 	return (1);
// }

// /* Gets home directory */
// char	*get_home_dir(void)
// {
// 	char	*home_dir;

// 	home_dir = NULL;
// 	if (list_has_value("HOME=", get()->env))
// 		home_dir = ft_strdup(get_env_value("HOME="));
// 	else
// 		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// 	return (home_dir);
// }

// /* Handle directories starting with '~' */
// char	*get_tilda_path(char *path)
// {
// 	char	*new_path;

// 	new_path = NULL;
// 	if (list_has_value("HOME=", get()->env))
// 		new_path = ft_strjoin(get_env_value("HOME="), path + 1);
// 	else
// 		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// 	free(path);
// 	return (new_path);
// }


// /* Processes path and returns a string allocated with malloc */
// char	*process_path(char *path)
// {
// 	char	*new_path;

// 	if (!path)
// 		return (get_home_dir());
// 	new_path = ft_strdup(path);
// 	if (!new_path)
// 		return (NULL);
// 	else if (new_path[0] == '-' && ft_strlen(new_path) == 1)
// 	{
// 		free(new_path);
// 		new_path = ft_strdup(get_env_value("OLDPWD="));
// 		if (!new_path || !new_path[0])
// 		{
// 			if (new_path)
// 				free(new_path);
// 			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
// 			return (NULL);
// 		}
// 		ft_putendl_fd(new_path, STDOUT_FILENO);
// 	}
// 	else if (new_path[0] == '~')
// 		new_path = get_tilda_path(new_path);
// 	return (new_path);
// }

// /* Updates the PWD from g_data.env to reflect directory change */
// void	update_pwd(void)
// {
// 	char	*res;
// 	char	*temp;

// 	temp = getcwd(NULL, 0);
// 	res = ft_strjoin("PWD=", temp);
// 	free(temp);
// 	if (list_has_value("PWD=", get()->env))
// 		modify_value(get()->env, "PWD=", res);
// 	else
// 		ft_lstadd_back(get()->env, ft_listilia(res));
// }

// /* Updates the OLDPWD from g_data.env to reflect directory change */
// void	update_oldpwd(char *old)
// {
// 	char	*res;

// 	res = ft_strjoin("OLDPWD=", old);
// 	if (list_has_value("OLDPWD=", get()->env))
// 		modify_value(get()->env, "OLDPWD=", res);
// 	else
// 		ft_lstadd_back(get()->env, ft_listilia(res));
// }

// int	ft_cd(char **path)
// {
// 	char	*new_path;
// 	char	*cwd;

// 	if (incorrect_args(path))
// 		return (1);
// 	new_path = process_path(path[1]);
// 	if (!new_path)
// 		return (1);
// 	cwd = getcwd(NULL, 0);
// 	if (chdir(new_path) == -1)
// 	{
// 		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
// 		perror(new_path);
// 		free_paths(new_path, cwd);
// 		return (1);
// 	}
// 	else
// 	{
// 		update_pwd();
// 		update_oldpwd(cwd);
// 	}
// 	free_paths(new_path, cwd);
// 	return (0);
// }
