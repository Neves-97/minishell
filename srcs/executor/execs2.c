#include "../../includes/minishell.h"

t_built	*is_builtin_cmd(char *cmd)
{
	t_built	*builtin;

	builtin = get()->builtins;
	while (builtin)
	{
		if (!ft_strncmp(cmd, builtin->cmd, ft_strlen(builtin->cmd) + 1))
			return (builtin);
		builtin = builtin->next;
	}
	return (NULL);
}
