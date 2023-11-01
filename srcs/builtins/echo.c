#include "minishell.h"

int	check_n(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-')
	{
		i++;
		if (!arg[i])
			return (0);
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int		has_flag;
	int		i;

	if (args[1])
		has_flag = check_n(args[1]);
	else
		has_flag = 0;
	i = 1;
	if (!args || !args[0])
		return (1); // TODO: Update status code **arg
	i = 1 + has_flag;
	while (args[i]) 
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (!has_flag)
		ft_printf("\n");
	return (0);
}
