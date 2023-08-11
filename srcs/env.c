#include "minishell.h"

void	inc_shlvl(char **env)
{
	int		i;
	char	*str;
	int		nbr;

	i = 0;
	while ((ft_strncmp(env[i], "SHLVL", 5)))
		i++;
	str = ft_substr(env[i], 6, ft_strlen(env[i]));
	nbr = ft_atoi(str);
	free(str);
	free(env[i]);
	str = (ft_itoa(nbr + 1));
	env[i] = ft_strjoin("SHLVL=", str);
	free(str);
}
