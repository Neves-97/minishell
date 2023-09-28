#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, PATH_MAX + 1))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}
