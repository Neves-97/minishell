/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:13:35 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:13:35 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_and_or(t_ast *root)
{
	if (!root)
		return ;
	if (root->type == AST_AND)
	{
		exec_and_or(root->left);
		if (get()->exit_status == 0)
			exec_and_or(root->right);
	}
	else if (root->type == AST_OR)
	{
		exec_and_or(root->left);
		if (get()->exit_status != 0)
			exec_and_or(root->right);
	}
	else
		execute_job(root);
}
