#include "minishell.h"

void	replace_env_var(char *var, t_list *tokens)
{
	int	pos;
	int	max;

	pos = 0;
	while (get()->env[pos] != NULL)
		pos++;
	max = pos;
	pos = search_env(var + 1);
	if (pos < max)
		tokens->content = ft_strdup(get()->env[pos] + ft_strlen(var));
	else
		tokens->content = NULL;
}

void	expand(t_list *tokens)
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
			replace_env_var(tmp, tokens);
			free (tmp);
		}
	}
}
