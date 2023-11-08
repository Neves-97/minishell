/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:16:41 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/08 15:16:44 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*redir(void)
{
	t_ast	*new_node;
	t_list	*backup;

	backup = get()->tokens_tmp;
	new_node = redir_case1();
	if (new_node)
		return (new_node);
	get()->tokens_tmp = backup;
	new_node = redir_case2();
	if (new_node)
		return (new_node);
	return (NULL);
}

// <redir in>

t_ast	*redir_case1(void)
{
	t_ast	*new_node;

	new_node = redir_in();
	if (!new_node)
		return (NULL);
	return (new_node);
}

// <redir out>

t_ast	*redir_case2(void)
{
	t_ast	*new_node;

	new_node = redir_out();
	if (!new_node)
		return (NULL);
	return (new_node);
}
