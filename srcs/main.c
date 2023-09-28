#include "minishell.h"

void	minishell(t_msh *data)
{
	lexer(data);
	// print_list(data->tokens);
	parser();
	// print_ast(get()->ast_tmp, 0);
	executor();
	free_nodes();
	free_ast(get()->ast_tmp);
}
int	main(int ac, char **av, char **envp)
{
	setup(get(), envp);
	(void)ac;
	(void)av;
	while (1)
	{
		get()->input = readline("minishell:~$ ");
		if (!get()->input)
			break ;
		if (!(is_whtspc(get()->input)))
			add_history(get()->input);
		minishell(get());
		free(get()->input);
	}
	free_ptp(get()->env);
	free_ptp(get()->export);
	return (0);
}
