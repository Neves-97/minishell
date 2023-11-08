/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:28 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:16:29 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*command(void)
{
	t_ast	*cmd_node;

	cmd_node = ast_new_node(AST_CMD);
	if (!cmd_node)
		return (NULL);
	get()->ast_tmp = cmd_node;
	if (!token_list())
		return (free_ast(cmd_node));
	return (cmd_node);
}
