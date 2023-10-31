#include "../../includes/minishell.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}

char	*get_env_value(char *value)
{
	char	**env;
	int		i;

	env = get()->env;
	i = 0;
	if (!*(get()->env) || !value || !*value)
		return ("");
	while (env[i])
	{
		if (!(ft_strncmp(env[i], value, ft_strlen(value))))
			return (env[i] + ft_strlen(value));
		i++;
	}
	return ("");
}

char	**get_argv_env(void)
{
	int		size;
	int		i;
	char	**env_copy;
	char	**env; // Assuming get()->env is a char**
	i = 0;
	size = 0;
	env = get()->env;
	while (env[size] != NULL) // Calculate the size of the char** array using a while loop
		size++;
	env_copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env_copy)
		return (NULL); // Handle allocation error
	while (env[i] != NULL) // Copy the char** data into the new array using a while loop
	{
		env_copy[i] = strdup(env[i]);
		if (!env_copy[i])
		{
			free(env_copy);
			return (NULL); // Handle allocation error
		}
		i++;
	}
	env_copy[size] = NULL; // Null-terminate the new char** array
	return (env_copy);
}
