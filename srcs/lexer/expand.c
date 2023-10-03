#include "minishell.h"

char	*replace_env_var(char *var)
{
	int	pos;
	int	max;

	pos = 0;
	while (get()->env[pos] != NULL)
		pos++;
	max = pos;
	pos = search_env(var + 1);
	if (pos < max)
		return (ft_strdup(get()->env[pos] + ft_strlen(var)));
	return (NULL);
}

int	expand(t_list *tokens)
{
	int		i;
	char	*tmp;

	i = 0;
	if (tokens)
	{
		if (tokens->content[i] == '$')
		{
			tmp = ft_strdup(tokens->content);
			free (tokens->content);
			tokens->content = replace_env_var(tmp);
			free (tmp);
			if (!tokens->content)
				return (0);
		}
	}
	return (1);
}
