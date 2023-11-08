/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:14:23 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:14:24 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens_ast(void)
{
	free_nodes();
	free_ast(get()->ast_tmp);
}

void	free_them_all(void)
{
	free_tokens_ast();
	free_ptp(get()->env);
	free_builtins();
}

void	hd_free(int *fd, char *input)
{
	close(fd[0]);
	free(input);
	free_them_all();
}
