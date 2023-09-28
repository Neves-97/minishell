#include "minishell.h"

int	ft_unset(char *arg)
{
	int		pos[3];
	char	**new_env;

	pos [0] = 0;
	while (get()->env[pos[0]] && \
	ft_strncmp(get()->env[pos[0]], arg, ft_strlen(arg)))
		pos[0]++;
	if (!get()->env[pos[0]])
		return (0);
	pos[2] = pos[0];
	while (get()->env[pos[0]])
		pos[0]++;
	new_env = ft_calloc(pos[0], sizeof(char *));
	pos[0] = 0;
	pos[1] = 0;
	while (get()->env[pos[0]])
	{
		if (pos[0] == pos[2])
			pos[0]++;
		new_env[pos[1]++] = ft_strdup(get()->env[pos[0]++]);
	}
	free_ptp(get()->env);
	get()->env = new_env;
	return (1);
}