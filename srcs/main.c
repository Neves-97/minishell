#include "minishell.h"

void	minishell(t_msh *data)
{
	lexer(data);
	parser();
	print_ast(get()->ast_tmp, 0);
	free_ast(get()->ast_tmp);
	free_nodes(data->tokens);
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
	// while (1)
	// {
	// 	data.input = readline("minishell:~$ ");
	// 	if (!(is_whtspc(data.input)))
	// 		add_history(data.input);
	// 	minishell(&data);
	// 	free (data.input);
	// }
	if (ac != 2)
		return (1);
	get()->input = av[1];
	minishell(get());
}
