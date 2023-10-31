// #include "../../includes/minishell.h"
#include <stdio.h>

int	ft_echo(char **args)
{
	int		new_line;
	int		has_flag;
	int		i;

	(void) new_line;
	has_flag = 1;
	i = 1;
	if (!args || !args[0])
		return (1); // TODO: Update status code **arg
	if (args[1] && args[1][0] == '-') {
		while (args[1][i]) {
			if (args[1][i] != 'n')
				has_flag = 0;
			i++;
		}
	} else {
		has_flag = 0;
	}
	i = 1 + has_flag;
	// char *final_str;
	while (args[i]) {
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!has_flag)
		printf("\n");
	return (0);
}

// int main(int argc, char **argv) {
// 	if (argc < 2) return 1;
// 	ft_echo(++argv);
// 	return 0;
// }
