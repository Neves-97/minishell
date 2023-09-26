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

int	main(int ac, char **av, char **envp)
{
	setup(get(), envp);
	(void)ac;
	(void)av;
	ft_cd("../..");
	ft_pwd();
	ft_env(get()->env);
	free_ptp(get()->env);
	free_ptp(get()->export);
	while (1)
	{
		get()->input = readline("minishell:~$ ");
		if (!get()->input)
			return (0);
		if (!(is_whtspc(get()->input)))
			add_history(get()->input);
		minishell(get());
		free(get()->input);
	}
}
