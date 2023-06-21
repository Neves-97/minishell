#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	static t_msh	data;

	(void)ac;
	(void)envp;
	(void)av;
	while (1)
	{
		data.input = readline("minishell:~$ ");
		// data.input = "echo ola| wc";
		if (!(is_whtspc(data.input)))
			add_history(data.input);
		minishell(&data);
		free (data.input);
	}
}

void	minishell(t_msh *data)
{
	lexer(data);
	print_list(data->tokens);
	free_nodes(data->tokens);
}
