#include "../../includes/minishell.h"

int	ft_pwd(char **arg)
{
	(void) arg;
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, PATH_MAX + 1))
	{
		write(1, cwd, ft_strlen(cwd));
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void	printf_and_free(char *str)
{
	ft_printf("declare -x %s\n", str);
	free (str);
}
