#include "minishell.h"

void	minishell(t_msh *data)
{
	lexer(data);
	// print_list(data->tokens);
	parser();
	print_ast(get()->ast_tmp, 0);
	free_nodes();
	free_ast(get()->ast_tmp);
}

void	setup(t_msh *data, char **envp)
{
	data->env = dup_ptp(envp);
	data->export = dup_ptp(envp);
	inc_shlvl(data->env);
	free_ptp(data->env);
	free_ptp(data->export);
}

int	main(int ac, char **av, char **envp)
{
	setup(get(), envp);
	(void)ac;
	(void)av;
	while (1)
	{
		get()->input = readline("minishell:~$ ");
		if (!(is_whtspc(get()->input)))
			add_history(get()->input);
		minishell(get());
		free(get()->input);
	}
	// if (ac != 2) 
	// 	return (1);
	// get()->input = av[1];
	// minishell(get());
}
