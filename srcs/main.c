/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:50 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/09 16:27:23 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// print_list(data->tokens);
// print_ast(get()->ast_tmp, 0);

void	minishell(t_msh *data)
{
	lexer(data);
	parser();
	executor();
	free_nodes();
	free_ast(get()->ast_tmp);
}

int	main(int ac, char **av, char **envp)
{
	setup(get(), envp);
	(void)ac;
	(void)av;
	parent_signals();
	while (1)
	{
		get()->child = FALSE;
		get()->input = readline("minishell:~$ ");
		if (!get()->input)
			break ;
		if (!(is_whtspc(get()->input)))
			add_history(get()->input);
		minishell(get());
		free(get()->input);
	}
	free_ptp(get()->env);
	free_builtins();
	// exit(get()->exit_status);
	return (get()->exit_status);
}
