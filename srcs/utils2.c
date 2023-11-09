/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:17:10 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 22:23:55 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_ast(t_ast *root, int spaces)
{
	if (!root)
		return ;
	if (root->right)
		print_ast(root->right, spaces + 5);
	for (int i = 0; i < spaces; i++)
		printf(" ");
	if (root->content)
		printf("%s, type: %d\n", root->content, root->type);
	if (root->left)
		print_ast(root->left, spaces + 5);
}

void	free_builtins(void)
{
	t_built	*tmp;

	while (get()->builtins)
	{
		tmp = get()->builtins->next;
		if (get()->builtins)
			free (get()->builtins);
		get()->builtins = tmp;
	}
}

int	*pqp(void)
{
	static int	a;

	return (&a);
}
